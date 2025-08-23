#pragma once

#include "godot_cpp/classes/camera3d.hpp"
#include "godot_cpp/classes/input.hpp"
#include "godot_cpp/classes/input_event.hpp"
#include "godot_cpp/classes/node3d.hpp"
#include "godot_cpp/classes/wrapped.hpp"
#include "godot_cpp/variant/vector2.hpp"

using namespace	godot;

class rtsCamera : public Node3D
{
  private:
	GDCLASS(rtsCamera, Node3D);
	float _movementSpeed;
	float _rotationSpeed;
	float _zoomSpeed;
	float _minZoom;
	float _maxZoom;
	float _minElevationAngle;
	float _maxElevationAngle;
	float _edgeMargin;
	bool _allowRotation;
	bool _allowZoom;
	bool _allowPan;
	Node3D *_Elevation;
	Camera3D *_camera3D;
	bool _isRotating;
	bool _isPanning;
	Vector2 _lastMousePosition;
	float _zoomLevel;
	void _handleKeyboardMovement(const float &delta);
	void _handleEdgeMovement(const float &delta);
	void _handleRotation(const float &delta);
	void _handleZoom(const float &delta);
	void _handlePanning(const float &delta);

  protected:
	static void _bind_methods();

  public:
	rtsCamera();

	void _process(float delta);
	void _ready() override;
};
