#include "./rtsCamera.hpp"
#include "godot_cpp/classes/input.hpp"
#include "godot_cpp/classes/input_event.hpp"
#include "godot_cpp/classes/object.hpp"
#include "godot_cpp/classes/ref.hpp"
#include "godot_cpp/core/print_string.hpp"
#include "godot_cpp/variant/vector2.hpp"
#include "godot_cpp/variant/vector3.hpp"

void rtsCamera::_bind_methods()
{
}

rtsCamera::rtsCamera() : _moveSpeed(0.8), _rotateKeySpeed(1.5), _zoomSpeed(3.0),
	_minZoom(-20), _maxZoom(20), _mouseSensitivity(0.2)
{
}

void rtsCamera::_ready()
{
	_rotateX = Object::cast_to<Node3D>(get_child(0));
	_pivot = Object::cast_to<Node3D>(_rotateX->get_child(0));
	_camera3d = Object::cast_to<Camera3D>(_pivot->get_child(0));
	_moveTarget = get_position();
	_rotateKeyTarget = get_rotation_degrees().y;
	_camera3d->set_position(_camera3d->get_position().lerp(Vector3(0, 0, 300),
			0.08));
	_camera3d->set_rotation_degrees(_camera3d->get_rotation_degrees().lerp(Vector3(-500,
				0, 0), 0.08));
	_zoomTarget = _camera3d->get_position().z;
	print_line(_camera3d->get_position(), _zoomTarget);
}

void rtsCamera::_process(float delta)
{
	Vector2	inputDir;
	Vector3	movementDir;
	float	rotateKey;
	int		zoomDir;

	inputDir = Input::get_singleton()->get_vector("ui_left", "ui_right",
			"ui_up", "ui_down");
	movementDir = (get_transform().basis.xform(Vector3(inputDir.x, 0,
					inputDir.y))).normalized();
	rotateKey = Input::get_singleton()->get_axis("rotate_left", "rotate_right");
	zoomDir = (((int)(Input::get_singleton()->is_action_just_released("zoom_out")))
			- ((int)(Input::get_singleton()->is_action_just_released("zoom_in"))));
	_moveTarget += _moveSpeed * movementDir;
	_rotateKeyTarget += rotateKey * _rotateKeySpeed;
	_zoomTarget += zoomDir * _zoomSpeed;
	set_position(get_position().lerp(_moveTarget, 0.08));
	set_rotation_degrees(get_rotation_degrees().lerp(Vector3(0,
				_rotateKeyTarget, 0), 0.05));
	_camera3d->set_position(_camera3d->get_position().lerp(Vector3(0,
				_zoomTarget, _zoomTarget), 0.06));
}

void rtsCamera::_unhandled_input(const Ref<InputEvent> &event)
{
	Vector2	tmp;

	if (event.is_valid() && event->is_action_pressed("rotate"))
	{
		print_line("lol");
	}
}
