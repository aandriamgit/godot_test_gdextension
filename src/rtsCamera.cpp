#include "./rtsCamera.hpp"
#include "godot_cpp/classes/object.hpp"

rtsCamera::rtsCamera() : _moveSpeed(0.6)
{
}

void rtsCamera::_ready()
{
	_rotateX = Object::cast_to<Node3D>(get_child(0));
	_pivot = Object::cast_to<Node3D>(_rotateX->get_child(0));
	_camera3d = Object::cast_to<Camera3D>(_pivot->get_child(0));
	_moveTarget = get_position();
}

void rtsCamera::_process(float delta)
{
}
