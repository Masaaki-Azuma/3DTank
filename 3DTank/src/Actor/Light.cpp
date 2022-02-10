#include "Light.h"

Light::Light(IWorld* world)
{
	world_ = world;
	name_ = "Light";
	tag_ = "LightTag";
}

void Light::draw() const
{
    float ambient[4] = { 0.2f, 0.2f, 0.2f, 1.0f };        // ライトの環境光カラー
    float diffuse[4] = { 1.0f, 1.0f, 1.0f, 1.0f };        // ライトの拡散反射光カラー
    float specular[4] = { 1.0f, 1.0f, 1.0f, 1.0f };       // ライトの鏡面反射光カラー
    float position[4] = { 0.0f, 100.0f, 0.0f, 0.0f }; // ライトの座標
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);            // 環境光カラーの設定
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);            // 拡散反射光カラーの設定
    glLightfv(GL_LIGHT0, GL_SPECULAR, specular);          // 鏡面反射光カラーの設定
    glLightfv(GL_LIGHT0, GL_POSITION, position);          // ライトの位置の設定
    glEnable(GL_LIGHT0);                                  // ライトの0番目を有効にする
    glEnable(GL_LIGHTING);                                // ライトを有効にする

}
