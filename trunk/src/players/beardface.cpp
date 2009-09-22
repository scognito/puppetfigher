#include "beardface.h"

extern u8 beardface_head_png[], beardface_torso_png[], beardface_bicep_png[], beardface_forearm_png[], beardface_hand_png[], beardface_thigh_png[], beardface_calf_png[], beardface_foot_png[];

extern u8 bullet_png[]; //,gun_png[];

extern char player_gsa[];

Beardface::Beardface(float x, float y, b2World* w):
	Player(x,y,player_gsa, w, 50, 30)
{
	InitArmor();
	InitWeapon();
}

Beardface::~Beardface()
{

}

void Beardface::InitWeapon()
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

void Beardface::InitArmor()
{
	//TODO Load this armor from some sort of player info	
	Armor::Type tArmor;
	
	tArmor.dx = 0;
	tArmor.dy = 0;
	tArmor.dang = 90;
	
	//Init Head
	tArmor.armor_type = Armor::Category::HEAD;
	tArmor.img = new Image();
	tArmor.img->LoadImage(beardface_head_png, IMG_LOAD_TYPE_BUFFER);
	this->SetArmor(tArmor);
	
	//Init Torso
	tArmor.dang = 270;
	tArmor.armor_type = Armor::Category::TORSO;
	tArmor.img = new Image();
	tArmor.img->LoadImage(beardface_torso_png, IMG_LOAD_TYPE_BUFFER);
	this->SetArmor(tArmor);
	
	tArmor.dang = 90;
	//Init Bicep
	tArmor.armor_type = Armor::Category::BICEP;
	tArmor.img = new Image();
	tArmor.img->LoadImage(beardface_bicep_png, IMG_LOAD_TYPE_BUFFER);
	this->SetArmor(tArmor);
	
	//Init forearm
	tArmor.armor_type = Armor::Category::FOREARM;
	tArmor.img = new Image();
	tArmor.img->LoadImage(beardface_forearm_png, IMG_LOAD_TYPE_BUFFER);
	this->SetArmor(tArmor);
	
	//Init hand
	tArmor.armor_type = Armor::Category::HAND;
	tArmor.img = new Image();
	tArmor.img->LoadImage(beardface_hand_png, IMG_LOAD_TYPE_BUFFER);
	this->SetArmor(tArmor);
	
	//Init Thigh
	tArmor.armor_type = Armor::Category::THIGH;
	tArmor.img = new Image();
	tArmor.img->LoadImage(beardface_thigh_png, IMG_LOAD_TYPE_BUFFER);
	this->SetArmor(tArmor);
	
	//Init CALF
	tArmor.armor_type = Armor::Category::CALF;
	tArmor.img = new Image();
	tArmor.img->LoadImage(beardface_calf_png, IMG_LOAD_TYPE_BUFFER);
	this->SetArmor(tArmor);
	
	//Init Foot
	tArmor.armor_type = Armor::Category::FOOT;
	tArmor.img = new Image();
	tArmor.img->LoadImage(beardface_foot_png, IMG_LOAD_TYPE_BUFFER);
	this->SetArmor(tArmor);
}
