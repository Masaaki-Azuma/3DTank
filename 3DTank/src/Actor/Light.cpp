#include "Light.h"

Light::Light(IWorld* world)
{
	world_ = world;
	name_ = "Light";
	tag_ = "LightTag";
}

void Light::draw() const
{
    float ambient[4] = { 0.2f, 0.2f, 0.2f, 1.0f };        // ���C�g�̊����J���[
    float diffuse[4] = { 1.0f, 1.0f, 1.0f, 1.0f };        // ���C�g�̊g�U���ˌ��J���[
    float specular[4] = { 1.0f, 1.0f, 1.0f, 1.0f };       // ���C�g�̋��ʔ��ˌ��J���[
    float position[4] = { 0.0f, 100.0f, 0.0f, 0.0f }; // ���C�g�̍��W
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);            // �����J���[�̐ݒ�
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);            // �g�U���ˌ��J���[�̐ݒ�
    glLightfv(GL_LIGHT0, GL_SPECULAR, specular);          // ���ʔ��ˌ��J���[�̐ݒ�
    glLightfv(GL_LIGHT0, GL_POSITION, position);          // ���C�g�̈ʒu�̐ݒ�
    glEnable(GL_LIGHT0);                                  // ���C�g��0�Ԗڂ�L���ɂ���
    glEnable(GL_LIGHTING);                                // ���C�g��L���ɂ���

}
