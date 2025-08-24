#pragma once

#include "godot_cpp/classes/camera3d.hpp"
#include "godot_cpp/classes/node3d.hpp"
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
	float _moveSpeed;
	Vector3 _moveTarget;

  public:
	rtsCamera();

	void _ready() override;
	void _process(float delta);
};
