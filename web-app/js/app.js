'use strict';

var _createClass = function () { function defineProperties(target, props) { for (var i = 0; i < props.length; i++) { var descriptor = props[i]; descriptor.enumerable = descriptor.enumerable || false; descriptor.configurable = true; if ("value" in descriptor) descriptor.writable = true; Object.defineProperty(target, descriptor.key, descriptor); } } return function (Constructor, protoProps, staticProps) { if (protoProps) defineProperties(Constructor.prototype, protoProps); if (staticProps) defineProperties(Constructor, staticProps); return Constructor; }; }();

function _classCallCheck(instance, Constructor) { if (!(instance instanceof Constructor)) { throw new TypeError("Cannot call a class as a function"); } }

function _possibleConstructorReturn(self, call) { if (!self) { throw new ReferenceError("this hasn't been initialised - super() hasn't been called"); } return call && (typeof call === "object" || typeof call === "function") ? call : self; }

function _inherits(subClass, superClass) { if (typeof superClass !== "function" && superClass !== null) { throw new TypeError("Super expression must either be null or a function, not " + typeof superClass); } subClass.prototype = Object.create(superClass && superClass.prototype, { constructor: { value: subClass, enumerable: false, writable: true, configurable: true } }); if (superClass) Object.setPrototypeOf ? Object.setPrototypeOf(subClass, superClass) : subClass.__proto__ = superClass; }

var e = React.createElement;
var updateIntervalMillis = 30;

function isNumeric(str) {
	if (typeof str != "string") return false;
	return !isNaN(str) && !isNaN(parseFloat(str));
}

var App = function (_React$Component) {
	_inherits(App, _React$Component);

	function App(props) {
		_classCallCheck(this, App);

		var _this = _possibleConstructorReturn(this, (App.__proto__ || Object.getPrototypeOf(App)).call(this, props));

		_this.setSelectionPos = function (pos) {
			var e = _this.state.env;
			if (_this.state.selection == "start") {
				e.start.x = pos.x;
				e.start.y = pos.y;
			} else if (_this.state.selection == "end") {
				e.end.x = pos.x;
				e.end.y = pos.y;
			} else if (_this.state.selection != null && _this.state.selection.lineId != null && _this.state.selection.endpoint != null) {
				e.walls.map(function (wall) {
					if (wall.id == _this.state.selection.lineId) {
						wall[_this.state.selection.endpoint].x = pos.x;
						wall[_this.state.selection.endpoint].y = pos.y;
					}
					return wall;
				});
			}
			_this.setState({ env: e, path: null });
		};

		_this.getSelectedAttributes = function () {
			var e = _this.state.env;
			if (_this.state.selection == "start") {
				return e.start;
			} else if (_this.state.selection == "end") {
				return e.end;
			} else if (_this.state.selection != null && _this.state.selection.lineId != null && _this.state.selection.endpoint != null) {
				return e.walls.filter(function (wall) {
					return wall.id == _this.state.selection.lineId;
				})[0][_this.state.selection.endpoint];
			}
			return {};
		};

		_this.computePath = function () {
			var wallVector = new Module.vector$Wall$();
			var walls = _this.state.env.walls.map(function (wall) {
				return new Module.Wall(new Module.Point(wall.point1.x, wall.point1.y, wall.point1.vx, wall.point1.vy), new Module.Point(wall.point2.x, wall.point2.y, wall.point2.vx, wall.point2.vy));
			}).forEach(function (wall) {
				return wallVector.push_back(wall);
			});
			var dypfEnv = new Module.Environment(_this.state.env.start, _this.state.env.end, wallVector, _this.state.env.speed, _this.state.env.timeStep);
			var solver = new Module.Solver(Module.getEnvironmentPointer(dypfEnv));
			var path = solver.solve();
			_this.setState({ path: path });
		};

		_this.setMode = function (mode) {
			_this.setState({ mode: mode, selection: null });
			if (mode != "pan") {
				var env = _this.state.env;
				env.time = 0;
				_this.setState({ env: env, paused: true });
			}
		};

		_this.onPlayClicked = function () {
			_this.setState({ paused: false, mode: "pan", selection: null });
			if (_this.state.path == null) {
				_this.computePath();
			}
		};

		_this.onPauseClicked = function () {
			_this.setState({ paused: true });
		};

		_this.onResetClicked = function () {
			var st = _this.state;
			st.paused = true;
			st.mode = "pan";
			st.env.time = 0;
			_this.setState(st);
		};

		_this.onRepeatClicked = function () {
			_this.setState({ repeat: !_this.state.repeat });
		};

		_this.onMouseDown = function (point) {
			if (_this.state.mode == "edit") {
				_this.setState({ selection: point, dragging: true });
			}
		};

		_this.onMouseUp = function () {
			_this.setState({ dragging: false });
			if (_this.state.showPath && _this.state.path == null) {
				_this.computePath();
			}
		};

		_this.onMouseMove = function (pos) {
			if (_this.state.dragging) {
				if (_this.state.paused && _this.state.selection != null) {
					_this.setSelectionPos(pos);
				}
			}
		};

		_this.onMouseClick = function (point) {
			if (_this.state.mode == "edit") {
				_this.setState({ selection: point });
			}
		};

		_this.wallStart = function (pos) {
			var env = _this.state.env;
			env.walls.push({
				id: _this.state.wallCount,
				point1: { x: pos.x, y: pos.y, vx: 0, vy: 0 },
				point2: { x: pos.x, y: pos.y, vx: 0, vy: 0 } });
			_this.setState({ path: null, env: env, selection: { lineId: _this.state.wallCount, endpoint: "point2" }, dragging: true, wallCount: _this.state.wallCount + 1 });
		};

		_this.wallEnd = function (pos) {
			_this.setState({ dragging: false });
			if (_this.state.showPath) {
				_this.computePath();
			}
		};

		_this.onInputChanged = function (field, value) {
			if (!isNumeric(value)) return;
			var v = parseFloat(value);
			var env = _this.state.env;
			if (field == "speed" || field == "timeStep") {
				env[field] = v;
			} else if (_this.state.selection == "start") {
				env.start[field] = v;
			} else if (_this.state.selection == "end") {
				env.end[field] = v;
			} else if (_this.state.selection != null && _this.state.selection.lineId != null && _this.state.selection.endpoint != null) {
				env.walls.map(function (wall) {
					if (wall.id == _this.state.selection.lineId) {
						wall[_this.state.selection.endpoint][field] = v;
					}
					return wall;
				});
			}
			_this.setState({ env: env, path: null });
			if (_this.state.showPath) {
				_this.computePath();
			}
		};

		_this.onCheckboxChanged = function (field, value) {
			if (field == "showPath") {
				_this.setState({ showPath: value });
				if (value && _this.state.env.path == null) {
					_this.computePath();
				}
			}
		};

		_this.onKeyDown = function (ev) {
			if (ev.key === "Backspace") {
				if (_this.state.selection != null && _this.state.selection.lineId != null && document.activeElement.tagName != "INPUT") {
					var env = _this.state.env;
					env.walls = env.walls.filter(function (wall) {
						return wall.id != _this.state.selection.lineId;
					});
					_this.setState({ env: env, selection: null, path: null });
					if (_this.state.showPath) {
						_this.computePath();
					}
				}
			}
		};

		_this.state = {
			env: {
				start: { x: 50, y: 50 },
				end: { x: 350, y: 250 },
				walls: [{
					id: 0,
					point1: { x: 100, y: 50, vx: 0, vy: 20 },
					point2: { x: 100, y: 150, vx: 20, vy: 0 }
				}],
				speed: 25,
				time: 0,
				timeStep: 1
			},
			paused: true,
			mode: "edit",
			path: null,
			selection: null,
			dragging: false,
			repeat: false
		};
		setInterval(function () {
			if (_this.state.paused == false && _this.state.path != null) {
				var st = _this.state;
				st.env.time += updateIntervalMillis / 1000;
				if (st.env.time > _this.state.path.getArriveTime()) {
					if (_this.state.repeat) {
						st.env.time = 0;
					} else {
						st.env.time = _this.state.path.getArriveTime();
					}
				}
				_this.setState(st);
			}
		}, updateIntervalMillis);
		_this.state.wallCount = _this.state.env.walls.length;
		document.addEventListener("keydown", _this.onKeyDown);
		return _this;
	}

	_createClass(App, [{
		key: "render",
		value: function render() {
			return React.createElement(
				"div",
				{ className: "container", onKeyDown: this.onKeyDown },
				React.createElement(
					"div",
					{ className: "row" },
					React.createElement(
						"div",
						{ className: "col" },
						React.createElement(ControlBar, { env: this.state.env, mode: this.state.mode, dragging: this.state.dragging,
							setMode: this.setMode, selectedAttributes: this.getSelectedAttributes(), onInputChanged: this.onInputChanged })
					)
				),
				React.createElement(
					"div",
					{ className: "row" },
					React.createElement(
						"div",
						{ className: "col" },
						React.createElement(Display, { env: this.state.env, path: this.state.path, mode: this.state.mode, selection: this.state.selection, showPath: this.state.showPath,
							wallStart: this.wallStart, wallEnd: this.wallEnd,
							onMouseMove: this.onMouseMove, onMouseDown: this.onMouseDown, onMouseUp: this.onMouseUp, onMouseClick: this.onMouseClick })
					)
				),
				React.createElement(
					"div",
					{ className: "row" },
					React.createElement(
						"div",
						{ className: "col" },
						React.createElement(PlayBar, { env: this.state.env,
							onPlayClicked: this.onPlayClicked, onPauseClicked: this.onPauseClicked, onResetClicked: this.onResetClicked, onRepeatClicked: this.onRepeatClicked,
							paused: this.state.paused, repeat: this.state.repeat, onInputChanged: this.onInputChanged, onCheckboxChanged: this.onCheckboxChanged })
					)
				)
			);
		}
	}]);

	return App;
}(React.Component);

var domContainer = document.querySelector('#app_container');
var app = React.createElement(App);
ReactDOM.render(app, domContainer);