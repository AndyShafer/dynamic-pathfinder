'use strict';

var _createClass = function () { function defineProperties(target, props) { for (var i = 0; i < props.length; i++) { var descriptor = props[i]; descriptor.enumerable = descriptor.enumerable || false; descriptor.configurable = true; if ("value" in descriptor) descriptor.writable = true; Object.defineProperty(target, descriptor.key, descriptor); } } return function (Constructor, protoProps, staticProps) { if (protoProps) defineProperties(Constructor.prototype, protoProps); if (staticProps) defineProperties(Constructor, staticProps); return Constructor; }; }();

function _classCallCheck(instance, Constructor) { if (!(instance instanceof Constructor)) { throw new TypeError("Cannot call a class as a function"); } }

function _possibleConstructorReturn(self, call) { if (!self) { throw new ReferenceError("this hasn't been initialised - super() hasn't been called"); } return call && (typeof call === "object" || typeof call === "function") ? call : self; }

function _inherits(subClass, superClass) { if (typeof superClass !== "function" && superClass !== null) { throw new TypeError("Super expression must either be null or a function, not " + typeof superClass); } subClass.prototype = Object.create(superClass && superClass.prototype, { constructor: { value: subClass, enumerable: false, writable: true, configurable: true } }); if (superClass) Object.setPrototypeOf ? Object.setPrototypeOf(subClass, superClass) : subClass.__proto__ = superClass; }

var Display = function (_React$Component) {
	_inherits(Display, _React$Component);

	function Display(props) {
		_classCallCheck(this, Display);

		var _this = _possibleConstructorReturn(this, (Display.__proto__ || Object.getPrototypeOf(Display)).call(this, props));

		_this.getStroke = function (obj) {
			if (_this.props.selection == null) {
				return "black";
			}
			if (_this.props.selection == obj || obj.lineId != null && obj.endpoint != null && _this.props.selection.lineId == obj.lineId && _this.props.selection.endpoint == obj.endpoint) {
				return "blue";
			}
			return "black";
		};

		_this.pathPos = function () {
			if (_this.props.path != null) {
				var pos = _this.props.path.getPos(_this.props.env.time);
				return React.createElement("circle", { cx: pos.x, cy: pos.y, r: "5", fill: "black" });
			}
			return null;
		};

		_this.drawPath = function () {
			var lines = [];
			if (_this.props.showPath && _this.props.path != null) {
				var segments = _this.props.path.getSegments();
				for (var i = 0; i < segments.size(); i++) {
					lines.push(React.createElement("line", { key: i, x1: segments.get(i).getStart().x, y1: segments.get(i).getStart().y, x2: segments.get(i).getEnd().x, y2: segments.get(i).getEnd().y, stroke: "#6699ff" }));
				}
			}
			return lines;
		};

		_this.wallSelectCircles = function (wall) {
			if (_this.props.mode == "edit") {
				return React.createElement(
					React.Fragment,
					null,
					React.createElement("circle", { cx: wall.point1.x + _this.props.env.time * wall.point1.vx,
						cy: wall.point1.y + _this.props.env.time * wall.point1.vy,
						r: "5", stroke: _this.getStroke({ lineId: wall.id, endpoint: "point1" }), strokeWidth: "2", fillOpacity: "0",
						onMouseDown: _this.mouseDown({ lineId: wall.id, endpoint: "point1" }), onMouseUp: _this.mouseUp,
						onClick: _this.mouseClick({ lineId: wall.id, endpoint: "point1" }) }),
					React.createElement("circle", { cx: wall.point2.x + _this.props.env.time * wall.point2.vx,
						cy: wall.point2.y + _this.props.env.time * wall.point2.vy,
						r: "5", stroke: _this.getStroke({ lineId: wall.id, endpoint: "point2" }), strokeWidth: "2", fillOpacity: "0",
						onMouseDown: _this.mouseDown({ lineId: wall.id, endpoint: "point2" }), onMouseUp: _this.mouseUp,
						onClick: _this.mouseClick({ lineId: wall.id, endpoint: "point2" }) })
				);
			}
		};

		_this.mouseDown = function (point) {
			return function () {
				return _this.props.onMouseDown(point);
			};
		};

		_this.mouseUp = function () {
			_this.props.onMouseUp();
		};

		_this.cursorPos = function (ev) {
			_this.pt.x = ev.clientX;
			_this.pt.y = ev.clientY;

			// The cursor point, translated into svg coordinates
			return _this.pt.matrixTransform(_this.svg.getScreenCTM().inverse());
		};

		_this.mouseMove = function (ev) {
			_this.props.onMouseMove(_this.cursorPos(ev));
		};

		_this.mouseClick = function (point) {
			return function () {
				return _this.props.onMouseClick(point);
			};
		};

		_this.wallStart = function (ev) {
			_this.props.wallStart(_this.cursorPos(ev));
		};

		_this.wallEnd = function (ev) {
			_this.props.wallEnd(_this.cursorPos(ev));
		};

		_this.panStart = function (ev) {
			_this.panOrigin = {};
			_this.panOrigin.x = ev.clientX;
			_this.panOrigin.y = ev.clientY;
			_this.startingOffset = _this.state.offset;
		};

		_this.panEnd = function () {
			_this.panOrigin = null;
		};

		_this.panMove = function (ev) {
			if (_this.panOrigin == null) return;
			var dx = ev.clientX - _this.panOrigin.x;
			var dy = ev.clientY - _this.panOrigin.y;

			var offset = {};
			offset.x = _this.startingOffset.x - dx;
			offset.y = _this.startingOffset.y - dy;

			_this.setState({ offset: offset });
		};

		_this.getViewBox = function () {
			return _this.state.offset.x + " " + _this.state.offset.y + " 1080 600";
		};

		_this.renderEnv = function () {
			return React.createElement(
				React.Fragment,
				null,
				React.createElement("circle", { cx: _this.props.env.start.x, cy: _this.props.env.start.y, r: "10", stroke: _this.getStroke("start"), strokeWidth: "2", fill: "green",
					onMouseDown: _this.mouseDown("start"), onMouseUp: _this.mouseUp, onClick: _this.mouseClick("start") }),
				React.createElement("circle", { cx: _this.props.env.end.x, cy: _this.props.env.end.y, r: "10", stroke: _this.getStroke("end"), strokeWidth: "2", fill: "red",
					onMouseDown: _this.mouseDown("end"), onMouseUp: _this.mouseUp, onClick: _this.mouseClick("end") }),
				_this.props.env.walls.map(function (wall) {
					return React.createElement(
						React.Fragment,
						{ key: wall.id },
						React.createElement("line", { x1: wall.point1.x + _this.props.env.time * wall.point1.vx,
							y1: wall.point1.y + _this.props.env.time * wall.point1.vy,
							x2: wall.point2.x + _this.props.env.time * wall.point2.vx,
							y2: wall.point2.y + _this.props.env.time * wall.point2.vy,
							stroke: "black", strokeWidth: "2" }),
						_this.wallSelectCircles(wall)
					);
				}),
				_this.drawPath(),
				_this.pathPos()
			);
		};

		_this.state = {
			offset: { x: 0, y: 0 }
		};
		return _this;
	}

	_createClass(Display, [{
		key: "componentDidMount",
		value: function componentDidMount() {
			this.pt = this.svg.createSVGPoint();
		}
	}, {
		key: "render",
		value: function render() {
			var _this2 = this;

			if (this.props.mode == "draw-wall") {
				return React.createElement(
					"svg",
					{ id: "display", width: "1080", height: "600", viewBox: this.getViewBox(), style: { border: '3px solid #000000' }, ref: function ref(_ref) {
							return _this2.svg = _ref;
						},
						onMouseMove: this.mouseMove, onMouseDown: this.wallStart, onMouseUp: this.wallEnd },
					this.renderEnv()
				);
			}
			if (this.props.mode == "pan") {
				return React.createElement(
					"svg",
					{ id: "display", width: "1080", height: "600", viewBox: this.getViewBox(), style: { border: '3px solid #000000', cursor: "move" }, ref: function ref(_ref2) {
							return _this2.svg = _ref2;
						},
						onMouseMove: this.panMove, onMouseDown: this.panStart, onMouseUp: this.panEnd },
					this.renderEnv()
				);
			}
			return React.createElement(
				"svg",
				{ id: "display", width: "1080", height: "600", viewBox: this.getViewBox(), style: { border: '3px solid #000000' }, ref: function ref(_ref3) {
						return _this2.svg = _ref3;
					}, onMouseMove: this.mouseMove },
				this.renderEnv()
			);
		}
	}]);

	return Display;
}(React.Component);