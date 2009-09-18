
#include <wiiuse/wpad.h>
#include <wiisprite.h>
#include <fat.h>

#include <Box2D.h>
#include "commontypes.h"

#include <vector.h>

#include <math.h>
#include <time.h>

using namespace wsp;

#define MAX_WIISPRITE_LAYERS 100

#include "warrior.h"
#include "bullet.h"
#include "entity.h"
#include "wasp.h"

#include "levelscreen.h"

extern u8 wasp_png[];
extern u8 layer0_png[];
extern u8 layer1_png[];
extern u8 layer2_png[];

Warrior* player = NULL;

b2World *world = 0;

int screen_width, screen_height;

const float32 timeStep          = 1.0f / 60.0f;
const int32 iterations          = 10;

//------------------------
// World test stuff
Rectangle ground_rect;
Quad ground_quad;

Rectangle block_rect;
Quad block_quad;

GXColor color = {70.0, 70.0, 70.0, 255.0};

b2Body *block;

std::vector<Bullet*> bullets;
std::vector<Entity*> enemies;

int MAX_WASPS = 20;

std::vector<Player*> remotePlayers;

Image* enemy_img;

LevelScreen* levelScreen;
Image* layer0_img;
Image* layer1_img;
Image* layer2_img;

//-------------------------

void SetupWorld(void)
{
	ground_rect.x = 0;
	ground_rect.y = 415;
	ground_rect.width = 640;
	ground_rect.height = 100;
	ground_quad.SetRectangle(&ground_rect);
	ground_quad.SetFillColor(color);
	
	
	block_rect.x = 200;
	block_rect.y = 300;
	block_rect.width = 50;
	block_rect.height = 50;
	block_quad.SetRectangle(&block_rect);
	block_quad.SetFillColor(color);
	
	
	b2BodyDef bodyDef;
	
	bodyDef.position.Set((block_rect.x + block_rect.width/2) / CommonTypes::PIXELS_PER_UNIT, (block_rect.y - block_rect.height)  / CommonTypes::PIXELS_PER_UNIT);
		
	bodyDef.angle = 0;
	block = world->CreateBody(&bodyDef);
	
	b2PolygonDef polydef;
	polydef.SetAsBox(((block_rect.width/CommonTypes::PIXELS_PER_UNIT)/2.0), ((block_rect.height/CommonTypes::PIXELS_PER_UNIT)/2.0));
	
  	polydef.density = 0.0; //fixed
		
	polydef.friction = CommonTypes::DEFAULT_FRICTION;
	polydef.restitution = CommonTypes::DEFAULT_RESTITUTION;
	
	block->CreateShape(&polydef);	
	
	block->SetMassFromShapes();
	
	//block_rect.height = 10;
	block_quad.SetRectangle(&block_rect);
}

void makeWorld(void)
{
	b2AABB worldAABB;
	// Visible area is 8x6 units
	worldAABB.lowerBound.Set(-8.0f, -6.0f);
	worldAABB.upperBound.Set(16.0f, 12.0f);
	b2Vec2 gravity(0.0f, 10.0f);
	bool doSleep = false;
	world = new b2World(worldAABB, gravity, doSleep);
	
	b2BodyDef groundBodyDef;
	groundBodyDef.position.Set(-1.0f, -1.0f);
	b2Body* groundBody = world->CreateBody(&groundBodyDef);
	
	// Get Screen Resolution
	// It turns out this is tricky because in a TV you never know your effective resolution and origin
	// So, I'm using works-for-me heuristics
	GXRModeObj *rmode = VIDEO_GetPreferredMode(NULL);
	screen_width = (int)((float)rmode->viWidth * 1.9f); 
	screen_height = (int)((float)rmode->viHeight * 0.9f);
	float32 width = (float)screen_width / CommonTypes::PIXELS_PER_UNIT;
	float32 height = (float)screen_height / CommonTypes::PIXELS_PER_UNIT;
	
	// Create a room
	b2PolygonDef groundShapeDef[4];
	groundShapeDef[0].SetAsBox(float32(width), float32(0.1f),   b2Vec2(width/2.0, -0.1),       0.0);
	groundShapeDef[1].SetAsBox(float32(width), float32(0.1f),   b2Vec2(width/2.0, height),     0.0);
	groundShapeDef[2].SetAsBox(float32(0.1f),  float32(height), b2Vec2(-0.1,      height/2.0), 0.0);
	groundShapeDef[3].SetAsBox(float32(0.1f),  float32(height), b2Vec2(width,     height/2.0), 0.0);
	
	for(int i=0;i<4;++i)
		groundBody->CreateShape(&groundShapeDef[i]);
}

void AddEntity()
{
    float x = rand()%20-10;
	float y = rand()%20-10;

	Wasp* e = new Wasp(200+x, 40+y, enemy_img);
    //
	enemies.push_back(e);
}

void AddPlayer()
{
	//Warrior* p = new Warrior(300,300, world);
	
	//remotePlayers.push_back(p);
}

int main(int argc, char **argv){


	WPAD_Init();
	PAD_Init();
	fatInitDefault();
	GameWindow gwd;
	gwd.InitVideo();
	gwd.SetBackground((GXColor){255, 255, 255, 255 });

	// make our LayerManager
	LayerManager layermanager(MAX_WIISPRITE_LAYERS);

	makeWorld();
	SetupWorld();
	
    //Test Thing to kill	
	layer0_img = new Image();
	layer0_img->LoadImage(layer0_png, IMG_LOAD_TYPE_BUFFER);
	
	layer1_img = new Image();
	layer1_img->LoadImage(layer1_png, IMG_LOAD_TYPE_BUFFER);
	
	layer2_img = new Image();
	layer2_img->LoadImage(layer2_png, IMG_LOAD_TYPE_BUFFER);
	
	levelScreen = new LevelScreen(layer0_img, layer1_img, layer2_img);
	
	player = new Warrior(300,300, world);
	
	float dx = 0;
	
    int i = 0;
	int FRAME_TICK = 30;

	//playerSkeleton->Print();
	
	int direction_x = 1;
	int direction_y = 0;
	
//	int flip_frame = 0;
	bool anim_override = false;
	bool flip_animation = false;
	int aim_count = 0;
	
	float _spawnTimer = 0;
	bool spawn_entity = false;
	
    std::vector<Bullet*>::iterator Iter;
    std::vector<Entity*>::iterator IterE;
    std::vector<Player*>::iterator IterP;


    //init rand
	srand(time(0));

    //Test Thing to kill	
	enemy_img = new Image();
	enemy_img->LoadImage(wasp_png, IMG_LOAD_TYPE_BUFFER);
	
	
	//Add remote entity for test
	AddEntity();
	
	//Add a remote player for test
	AddPlayer();
	
	float shiftx = 0;
	
	for(;;){
	
	    levelScreen->DrawBackground();
	
		WPAD_ScanPads();
		PAD_ScanPads();
		if(WPAD_ButtonsDown(WPAD_CHAN_0)&WPAD_BUTTON_HOME)
			break;
			
		if(WPAD_ButtonsHeld(WPAD_CHAN_0)&WPAD_BUTTON_RIGHT || PAD_ButtonsHeld(0)&PAD_BUTTON_RIGHT)
		{
		
			dx += 0.1;
			if(dx > 1.5) dx = 1.5;
			direction_x = 1;
			direction_y = 0;
			anim_override = false;
			flip_animation = false;
			levelScreen->ScrollRight(2.0);
			player->MovePlayer(dx,0);
			shiftx-=2.0;
		}
		
		if(WPAD_ButtonsHeld(WPAD_CHAN_0)&WPAD_BUTTON_LEFT || PAD_ButtonsHeld(0)&PAD_BUTTON_LEFT)
		{
			dx -= 0.1;
			if(abs(dx) > 1.5) dx = -1.5;
			direction_x = -1;
			direction_y = 0;
			anim_override = false;
			flip_animation = true;
			levelScreen->ScrollLeft(2.0);
			player->MovePlayer(dx,0);
			shiftx+=2.0;
		}
		
		if(WPAD_ButtonsHeld(WPAD_CHAN_0)&WPAD_BUTTON_UP || PAD_ButtonsHeld(0)&PAD_BUTTON_UP)
		{
			direction_y = -1;
			anim_override = false;
		}
		else
		{
			direction_y = 0;
		}
		
		if(WPAD_ButtonsDown(WPAD_CHAN_0)&WPAD_BUTTON_A || PAD_ButtonsDown(0)&PAD_BUTTON_A)
		{
			player->Jump();
		}
		
		if(WPAD_ButtonsDown(WPAD_CHAN_0)&WPAD_BUTTON_B || PAD_ButtonsDown(0)&PAD_BUTTON_B)
		{
		    //Fire
			//TODO Care about pointer location?
			
			b2Vec2 tDirection(direction_x,direction_y);
			
			if(direction_x == 0 &&direction_y == 0)
			{
				if(flip_animation) tDirection.x = -1;
				else tDirection.x = 1;
			}
			
			//tDirection.Normalize();
			Bullet* tBullet = player->FireWeapon(tDirection);
			
			aim_count = 20;
			
			if(tBullet != NULL)
			{
			   bullets.push_back(tBullet);
			}
		}
		
		
		if(WPAD_ButtonsDown(WPAD_CHAN_0)&WPAD_BUTTON_PLUS || PAD_ButtonsDown(0)&PAD_TRIGGER_R)
		{
			anim_override = true;
			player->SetCurrentAnimation(player->GetCurrentAnimation()+1);
		}
		
		if(WPAD_ButtonsDown(WPAD_CHAN_0)&WPAD_BUTTON_MINUS|| PAD_ButtonsDown(0)&PAD_TRIGGER_L)
		{
			anim_override = true;
			player->SetCurrentAnimation(player->GetCurrentAnimation()-1);
		}
		
		if(!(WPAD_ButtonsHeld(WPAD_CHAN_0)&WPAD_BUTTON_RIGHT || PAD_ButtonsHeld(0)&PAD_BUTTON_RIGHT) &&
		   !(WPAD_ButtonsHeld(WPAD_CHAN_0)&WPAD_BUTTON_LEFT || PAD_ButtonsHeld(0)&PAD_BUTTON_LEFT))
		{
			dx = 0;
			direction_x = 0;
		}
		
		if(!anim_override)
			player->MovePlayer(dx,0);
			
		if(i == FRAME_TICK) i = 0;
		else i++;
		
		 for (IterE = enemies.begin(); IterE != enemies.end(); IterE++ )
		{
		   //type wasp
		   if(((Entity*)*IterE)->IsAlive())
		   {
			  ((Wasp*)*IterE)->Render(shiftx);
		   }
		}	
		
		 for (Iter = bullets.begin(); Iter != bullets.end(); Iter++ )
		{
		   if(((Bullet*)*Iter)->Update())
		   {
				 for (IterE = enemies.begin(); IterE != enemies.end(); IterE++ )
				{
				   if(((Entity*)*IterE)->IsAlive())
				   {
						if(!((Entity*)*IterE)->CheckHit(((Bullet*)*Iter)))
						{
							((Bullet*)*Iter)->Delete();
						}
				   }
				}	
				
		        ((Bullet*)*Iter)->Draw();
		   }
		   else
		   {
		      //BIG TODO, fix this error when erasing from the list
			  //bullets.erase(Iter);
		   }
		}	
		
		
		player->SetFlip(flip_animation);
		player->StepAnimation(FRAME_TICK, i);
		
		if(aim_count > 0)
		{
		   if(direction_y != -1)
		   {
		      player->AimArm(0);
		   }
		   else if(direction_y == -1 && abs(direction_x) == 1)
		   {
		      player->AimArm(-45);
		   }
		   else if(direction_y == -1)
		   {
		      player->AimArm(-90);
		   }
		   
		   aim_count--;
		}
		
		player->Render();
		
		
		for (IterP = remotePlayers.begin(); IterP != remotePlayers.end(); IterP++ )
		{
			  ((Player*)*IterP)->Render();
		}	  
		
		
		ground_quad.Draw();
		block_quad.Draw();
		
		levelScreen->DrawForeground();
		
		gwd.Flush();
		world->Step(timeStep, iterations);
		
		//For fun, keep adding wasps every few seconds
		if(_spawnTimer >= 150)
		{
			spawn_entity = true;
			_spawnTimer = 0;
		}
		
		_spawnTimer++;
		
		if(spawn_entity)
		{
			AddEntity();
			spawn_entity = false;
		}
		
	}
	
	
	return 0;
}
