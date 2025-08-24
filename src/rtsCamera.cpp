#include "./rtsCamera.hpp"
#include "godot_cpp/classes/input.hpp"
#include "godot_cpp/classes/object.hpp"
#include "godot_cpp/variant/vector2.hpp"
#include "godot_cpp/variant/vector3.hpp"

void rtsCamera::_bind_methods()
{
}

rtsCamera::rtsCamera() : _moveSpeed(0.8)
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
	Vector2	inputDir;
	Vector3	movementDir;

	inputDir = Input::get_singleton()->get_vector("ui_left", "ui_right",
			"ui_up", "ui_down");
	movementDir = (get_transform().basis.xform(Vector3(inputDir.x, 0,
					inputDir.y))).normalized();
	_moveTarget += _moveSpeed * movementDir;
	set_position(get_position().lerp(_moveTarget, 0.08));
}
