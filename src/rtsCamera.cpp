#include "./rtsCamera.hpp"
#include "godot_cpp/classes/camera3d.hpp"
#include "godot_cpp/classes/input.hpp"
#include "godot_cpp/classes/input_event.hpp"
#include "godot_cpp/classes/node3d.hpp"
#include "godot_cpp/classes/object.hpp"
#include "godot_cpp/classes/viewport.hpp"
#include "godot_cpp/core/math.hpp"
#include "godot_cpp/variant/vector2.hpp"
#include "godot_cpp/variant/vector3.hpp"

void rtsCamera::_bind_methods()
{
}

void rtsCamera::_handleKeyboardMovement(const float &delta)
{
	Vector3 dir(0, 0, 0);
	if (Input::get_singleton()->is_action_pressed("ui_up")
		|| Input::get_singleton()->is_action_pressed("uiRtsUp"))
		dir.z = dir.z - 1;
	if (Input::get_singleton()->is_action_pressed("ui_down")
		|| Input::get_singleton()->is_action_pressed("uiRtsDown"))
		dir.z = dir.z + 1;
	if (Input::get_singleton()->is_action_pressed("ui_left")
		|| Input::get_singleton()->is_action_pressed("uiRtsLeft"))
		dir.x = dir.x - 1;
	if (Input::get_singleton()->is_action_pressed("ui_right")
		|| Input::get_singleton()->is_action_pressed("uiRtsRight"))
		dir.x = dir.x + 1;
	if (dir != Vector3(0, 0, 0))
	{
		dir = dir.normalized();
		global_translate(dir * _movementSpeed * delta);
	}
}

void rtsCamera::_handleEdgeMovement(const float &delta)
{
}

void rtsCamera::_handleRotation(const float &delta)
{
	Vector2	mouseDeplacement;
	float	elevationAngle;

	if (_isRotating == true)
	{
		mouseDeplacement = get_viewport()->get_mouse_position()
			- _lastMousePosition;
		_lastMousePosition = get_viewport()->get_mouse_position();
		rotate_y(Math::deg_to_rad(mouseDeplacement.x * _rotationSpeed * delta));
		elevationAngle = Math::rad_to_deg(_Elevation->get_rotation().x);
		elevationAngle = Math::clamp(elevationAngle - mouseDeplacement.y
				* _rotationSpeed * delta, -_maxElevationAngle,
				-_minElevationAngle);
		_Elevation->rotate_x(Math::deg_to_rad(elevationAngle));
	}
}

void rtsCamera::_handleZoom(const float &delta)
{
}

void rtsCamera::_handlePanning(const float &delta)
{
}

void rtsCamera::_process(float delta)
{
	_handleKeyboardMovement(delta);
	_handleRotation(delta);
}

void rtsCamera::_ready()
{
	_Elevation = Object::cast_to<Node3D>(get_child(0));
	_camera3D = Object::cast_to<Camera3D>(_Elevation->get_child(0));
}

rtsCamera::rtsCamera() : _movementSpeed(64), _rotationSpeed(5), _zoomSpeed(50),
	_minZoom(32), _maxZoom(256), _minElevationAngle(10), _maxElevationAngle(90),
	_edgeMargin(50), _allowRotation(true), _allowZoom(true), _allowPan(true),
	_Elevation(nullptr), _camera3D(nullptr), _isRotating(false),
	_isPanning(false), _zoomLevel(64)
{
}
