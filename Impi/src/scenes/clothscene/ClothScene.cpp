#include <src/scenes/clothscene/ClothScene.h>

ClothScene::ClothScene(Camera& camera, real clothWidth, real clothHeight)
	: Scene("ClothScene",
		camera,
		"src/scenes/clothscene/cloth.vert",
		"src/scene/clothscene/cloth.frag",
		nullptr), 
		clothWidth(clothWidth), 
		clothHeight(clothHeight),
		cloth(clothWidth, clothHeight, 55, 45)
{
	
}