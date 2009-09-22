
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

std::vector<Player*> players;

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
	
	
	//b2BodyDef bodyDef;
	
	//bodyDef.position.Set((block_rect.x + block_rect.width/2) / CommonTypes::PIXELS_PER_UNIT, (block_rect.y - block_rect.height)  / CommonTypes::PIXELS_PER_UNIT);
		
	//bodyDef.angle = 0;
	//block = world->CreateBody(&bodyDef);
	
	//b2PolygonDef polydef;
	//polydef.SetAsBox(((block_rect.width/CommonTypes::PIXELS_PER_UNIT)/2.0), ((block_rect.height/CommonTypes::PIXELS_PER_UNIT)/2.0));
	
  	//polydef.density = 0.0; //fixed
		
	//polydef.friction = CommonTypes::DEFAULT_FRICTION;
	//polydef.restitution = CommonTypes::DEFAULT_RESTITUTION;
	
	//block->CreateShape(&polydef);	
	
	//block->SetMassFromShapes();
	
	//block_rect.height = 10;
	//block_quad.SetRectangle(&block_rect);
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
	groundBodyDef.position.Set(0.0f, -1.0f);
	b2Body* groundBody = world->CreateBody(&groundBodyDef);
	
	// Get Screen Resolution
	// It turns out this is tricky because in a TV you never know your effective resolution and origin
	// So, I'm using works-for-me heuristics
	GXRModeObj *rmode = VIDEO_GetPreferredMode(NULL);
	screen_width = (int)((float)rmode->viWidth * 1.0f); 
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
    //float x = rand()%20-10;
	//float y = rand()%20-10;

	//Wasp* e = new Wasp(200+x, 40+y, enemy_img);
    //
	//enemies.push_back(e);
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
	
	players.push_back(new Warrior(250, 0, world));
	players[0]->MovePlayer(-50, 0, true);
	players.push_back(new Warrior(350,0, world));
	players[1]->MovePlayer(100, 0, true);
	
	std::vector<float> dx;
	std::vector<int>  direction_x;
	std::vector<int>  direction_y;
	std::vector<bool>  anim_override;
	std::vector<bool>  flip_animation;
	
	for(unsigned int np = 0; np < players.size(); np++)
	{
		dx.push_back(0);
		direction_x.push_back(1);
		direction_y.push_back(0);
		flip_animation.push_back(false);
		anim_override.push_back(false);
	}
	
    int i = 0;
	int FRAME_TICK = 25;

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
	
	
	int IDLE_ANIMATION = 0;
	int RUN_ANIMATION  = 1;
	int KICK_ANIMATION = 2;
	int PUNCH_ANIMATION = 3;
	
	for(;;){
	
	    levelScreen->DrawBackground();
	
		WPAD_ScanPads();
		PAD_ScanPads();
		
		ground_quad.Draw();
		
		
		for(unsigned int current_player = 0; current_player < players.size(); current_player++)
		{
			bool anim_set = false;
			if(WPAD_ButtonsDown(current_player)&WPAD_BUTTON_HOME)
				break;
				
			if(WPAD_ButtonsHeld(current_player)&WPAD_BUTTON_RIGHT || PAD_ButtonsHeld(current_player)&PAD_BUTTON_RIGHT)
			{
			
				dx[current_player] += 0.1;
				if(dx[current_player] > 1.5) dx[current_player] = 1.5;
				direction_x[current_player] = 1;
				direction_y[current_player] = 0;
				anim_override[current_player] = false;
				flip_animation[current_player] = false;
				//levelScreen->ScrollRight(2.0);
				players[current_player]->MovePlayer(dx[current_player],0);
				if(players[current_player]->GetCurrentAnimation() != RUN_ANIMATION)
					players[current_player]->SetCurrentAnimation(RUN_ANIMATION);
				
				anim_set = true;
			}
			else if(WPAD_ButtonsHeld(current_player)&WPAD_BUTTON_LEFT || PAD_ButtonsHeld(current_player)&PAD_BUTTON_LEFT)
			{
				dx[current_player] -= 0.1;
				if(abs(dx[current_player]) > 1.5) dx[current_player] = -1.5;
				direction_x[current_player] = -1;
				direction_y[current_player] = 0;
				anim_override[current_player] = false;
				flip_animation[current_player] = true;
				//levelScreen->ScrollLeft(2.0);
				if(players[current_player]->GetCurrentAnimation() != RUN_ANIMATION)
					players[current_player]->SetCurrentAnimation(RUN_ANIMATION);
				players[current_player]->MovePlayer(dx[current_player],0);
				
				anim_set = true;
			}
			
			if(WPAD_ButtonsHeld(current_player)&WPAD_BUTTON_UP || PAD_ButtonsHeld(current_player)&PAD_BUTTON_UP)
			{
				players[current_player]->Jump();
			}
			
			if(WPAD_ButtonsDown(current_player)&WPAD_BUTTON_A || PAD_ButtonsDown(current_player)&PAD_BUTTON_A)
			{
				players[current_player]->SetCurrentAnimation(KICK_ANIMATION,IDLE_ANIMATION);
				anim_set = true;
			}
			else if(WPAD_ButtonsDown(current_player)&WPAD_BUTTON_B || PAD_ButtonsDown(current_player)&PAD_BUTTON_B)
			{
				players[current_player]->SetCurrentAnimation(PUNCH_ANIMATION,IDLE_ANIMATION);
				anim_set = true;
			}
			
			if(!anim_set)
				players[current_player]->SetCurrentAnimation(IDLE_ANIMATION);
				
			
			players[current_player]->SetFlip(flip_animation[current_player]);
			players[current_player]->StepAnimation(FRAME_TICK, i);
			
			players[current_player]->Render();
		
		}
		
		if(i == FRAME_TICK) i = 0;
		else i++;
		
		levelScreen->DrawForeground();
		
		gwd.Flush();
		world->Step(timeStep, iterations);
		
		
	}
	
	
	return 0;
}
