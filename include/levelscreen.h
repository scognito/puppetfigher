#ifndef _LevelScreen_H_
#define _LevelScreen_H_

#include <wiisprite.h>

using namespace wsp;

class LevelScreen {
   public:
      LevelScreen(Image* layer_0, Image* layer_1, Image* layer_2);
	  ~LevelScreen();
	  
	  void ScrollRight(float distance);
	  void ScrollLeft(float distance);
	  
	  void DrawBackground();
	  void DrawForeground();
	  
   private:
      Sprite layer0_a, layer0_b;
	  Sprite layer1_a, layer1_b;
	  Sprite layer2_a, layer2_b;
};

#endif //_LevelScreen_H_
