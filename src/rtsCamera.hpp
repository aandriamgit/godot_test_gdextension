#pragma once

#include "godot_cpp/classes/camera3d.hpp"
#include "godot_cpp/classes/input_event.hpp"
#include "godot_cpp/classes/node3d.hpp"
#include "godot_cpp/classes/ref.hpp"
#include "godot_cpp/variant/vector3.hpp"

using namespace	godot;

class rtsCamera : public godot::Node3D
{
  private:
	GDCLASS(rtsCamera, Node3D);

  protected:
	static void _bind_methods();
	Node3D *_rotateX;
	Node3D *_pivot;
	Camera3D *_camera3d;
	Vector3 _moveTarget;
	float _moveSpeed;
	float _rotateKeySpeed;
	float _rotateKeyTarget;
	float _zoomSpeed;
	float _zoomTarget;
	float _minZoom;
	float _maxZoom;
	float _mouseSensitivity;

  public:
	rtsCamera();

	void _ready() override;
	void _process(float delta);
	void _unhandled_input(const Ref<InputEvent> &event) override;
};
