#include "levelscreen.h"


LevelScreen::LevelScreen(Image* layer_0, Image* layer_1, Image* layer_2)
{
   layer0_a.SetImage(layer_0);
   layer0_a.SetPosition(0,0);
   layer0_b.SetImage(layer_0);
   layer0_b.SetPosition(0,0);
   
   layer1_a.SetImage(layer_1);
   layer1_a.SetPosition(0,0);
   layer1_b.SetImage(layer_1);
   layer1_b.SetPosition(0,0);
   
   layer2_a.SetImage(layer_2);
   layer2_a.SetPosition(0,0);
   layer2_b.SetImage(layer_2);
   layer2_b.SetPosition(0,0);
}

LevelScreen::~LevelScreen()
{

}
	  
void LevelScreen::ScrollLeft(float distance)
{
   layer2_a.SetPosition((int)layer2_a.GetX()%640,0);
   layer1_a.SetPosition((int)layer1_a.GetX()%640,0);
   layer0_a.SetPosition((int)layer0_a.GetX()%640,0);

   layer2_a.SetPosition(layer2_a.GetX()+distance, 0);
   
   if(layer2_a.GetX() >= 0)
   {
      layer2_b.SetPosition(layer2_a.GetX()-640.0,0);
   }
   else
   {
      layer2_b.SetPosition(layer2_a.GetX()+640.0,0);
   }
   
   layer1_a.SetPosition(layer1_a.GetX()+distance/2.0, 0);
   
   if(layer1_a.GetX() >= 0)
   {
      layer1_b.SetPosition(layer1_a.GetX()-640.0,0);
   }
   else
   {
      layer1_b.SetPosition(layer1_a.GetX()+640.0,0);
   }
   
   layer0_a.SetPosition(layer0_a.GetX()+distance/4.0, 0);
   
   if(layer0_a.GetX() >= 0)
   {
      layer0_b.SetPosition(layer0_a.GetX()-640.0,0);
   }
   else
   {
      layer0_b.SetPosition(layer0_a.GetX()+640.0,0);
   }
}

void LevelScreen::ScrollRight(float distance)
{
   if(layer2_a.GetX() < -640) layer2_a.SetPosition(layer2_a.GetX()+640,0);
   if(layer1_a.GetX() < -640) layer2_a.SetPosition(layer1_a.GetX()+640,0);
   if(layer0_a.GetX() < -640) layer2_a.SetPosition(layer0_a.GetX()+640,0);
   
   layer2_a.SetPosition(layer2_a.GetX()-distance, 0);
   
   if(layer2_a.GetX() >= 0)
   {
      layer2_b.SetPosition(layer2_a.GetX()-640.0,0);
   }
   else
   {
      layer2_b.SetPosition(layer2_a.GetX()+640.0,0);
   }
   
   layer1_a.SetPosition(layer1_a.GetX()-distance/2.0, 0);
   
   if(layer1_a.GetX() >= 0)
   {
      layer1_b.SetPosition(layer1_a.GetX()-640.0,0);
   }
   else
   {
      layer1_b.SetPosition(layer1_a.GetX()+640.0,0);
   }
   
   layer0_a.SetPosition(layer0_a.GetX()-distance/4.0, 0);
   
   if(layer0_a.GetX() >= 0)
   {
      layer0_b.SetPosition(layer0_a.GetX()-640.0,0);
   }
   else
   {
      layer0_b.SetPosition(layer0_a.GetX()+640.0,0);
   }
}
	  
void LevelScreen::DrawBackground()
{
   layer0_a.Draw();
  // layer0_b.Draw();
   
   //layer1_a.Draw();
   //layer1_b.Draw();
}

void LevelScreen::DrawForeground()
{
   //layer2_a.Draw();
   //layer2_b.Draw();
}
