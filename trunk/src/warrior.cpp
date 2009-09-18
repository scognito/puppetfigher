#include "warrior.h"

extern u8 head_png[], torso_png[], bicep_png[], forearm_png[], hand_png[], thigh_png[], calf_png[], foot_png[];

extern u8 bullet_png[]; //,gun_png[];

extern char warrior_gsa[];

Warrior::Warrior(float x, float y, b2World* w):
	Player(x,y,warrior_gsa, w, 50, 30)
{
	InitArmor();
	InitWeapon();
}

Warrior::~Warrior()
{

}

void Warrior::InitWeapon()
{
    Weapon::Type tWeapon;
	tWeapon.dx = 0;
	tWeapon.dy = 0;
	tWeapon.dang = 0;
	
	//tWeapon.img = new Image();
	//tWeapon.img->LoadImage(gun_png, IMG_LOAD_TYPE_BUFFER);
	
	tWeapon.bullet_image = new Image();
	tWeapon.bullet_image->LoadImage(bullet_png, IMG_LOAD_TYPE_BUFFER);
	
	tWeapon.velocity          = 18.0;
	tWeapon.bullet_strength   = 5.0;
	tWeapon.power_consumption = 1.0;
	tWeapon.firing_delay      = 3.0;
	
	tWeapon.max_tof = 100;
	
	this->SetWeapon(tWeapon);
}

void Warrior::InitArmor()
{
	//TODO Load this armor from some sort of player info	
	Armor::Type tArmor;
	
	tArmor.dx = 0;
	tArmor.dy = 0;
	tArmor.dang = 90;
	
	//Init Head
	tArmor.armor_type = Armor::Category::HEAD;
	tArmor.img = new Image();
	tArmor.img->LoadImage(head_png, IMG_LOAD_TYPE_BUFFER);
	this->SetArmor(tArmor);
	
	//Init Torso
	tArmor.dang = 270;
	tArmor.armor_type = Armor::Category::TORSO;
	tArmor.img = new Image();
	tArmor.img->LoadImage(torso_png, IMG_LOAD_TYPE_BUFFER);
	this->SetArmor(tArmor);
	
	tArmor.dang = 90;
	//Init Bicep
	tArmor.armor_type = Armor::Category::BICEP;
	tArmor.img = new Image();
	tArmor.img->LoadImage(bicep_png, IMG_LOAD_TYPE_BUFFER);
	this->SetArmor(tArmor);
	
	//Init forearm
	tArmor.armor_type = Armor::Category::FOREARM;
	tArmor.img = new Image();
	tArmor.img->LoadImage(forearm_png, IMG_LOAD_TYPE_BUFFER);
	this->SetArmor(tArmor);
	
	//Init hand
	tArmor.armor_type = Armor::Category::HAND;
	tArmor.img = new Image();
	tArmor.img->LoadImage(hand_png, IMG_LOAD_TYPE_BUFFER);
	this->SetArmor(tArmor);
	
	//Init Thigh
	tArmor.armor_type = Armor::Category::THIGH;
	tArmor.img = new Image();
	tArmor.img->LoadImage(thigh_png, IMG_LOAD_TYPE_BUFFER);
	this->SetArmor(tArmor);
	
	//Init CALF
	tArmor.armor_type = Armor::Category::CALF;
	tArmor.img = new Image();
	tArmor.img->LoadImage(calf_png, IMG_LOAD_TYPE_BUFFER);
	this->SetArmor(tArmor);
	
	//Init Foot
	tArmor.armor_type = Armor::Category::FOOT;
	tArmor.img = new Image();
	tArmor.img->LoadImage(foot_png, IMG_LOAD_TYPE_BUFFER);
	this->SetArmor(tArmor);
}
