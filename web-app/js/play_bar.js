'use strict';

var _createClass = function () { function defineProperties(target, props) { for (var i = 0; i < props.length; i++) { var descriptor = props[i]; descriptor.enumerable = descriptor.enumerable || false; descriptor.configurable = true; if ("value" in descriptor) descriptor.writable = true; Object.defineProperty(target, descriptor.key, descriptor); } } return function (Constructor, protoProps, staticProps) { if (protoProps) defineProperties(Constructor.prototype, protoProps); if (staticProps) defineProperties(Constructor, staticProps); return Constructor; }; }();

function _classCallCheck(instance, Constructor) { if (!(instance instanceof Constructor)) { throw new TypeError("Cannot call a class as a function"); } }

function _possibleConstructorReturn(self, call) { if (!self) { throw new ReferenceError("this hasn't been initialised - super() hasn't been called"); } return call && (typeof call === "object" || typeof call === "function") ? call : self; }

function _inherits(subClass, superClass) { if (typeof superClass !== "function" && superClass !== null) { throw new TypeError("Super expression must either be null or a function, not " + typeof superClass); } subClass.prototype = Object.create(superClass && superClass.prototype, { constructor: { value: subClass, enumerable: false, writable: true, configurable: true } }); if (superClass) Object.setPrototypeOf ? Object.setPrototypeOf(subClass, superClass) : subClass.__proto__ = superClass; }

var PlayBar = function (_React$Component) {
	_inherits(PlayBar, _React$Component);

	function PlayBar(props) {
		_classCallCheck(this, PlayBar);

		var _this = _possibleConstructorReturn(this, (PlayBar.__proto__ || Object.getPrototypeOf(PlayBar)).call(this, props));

		_this.play = function () {
			_this.props.onPlayClicked();
		};

		_this.pause = function () {
			_this.props.onPauseClicked();
		};

		_this.reset = function () {
			_this.props.onResetClicked();
		};

		_this.repeat = function () {
			_this.props.onRepeatClicked();
		};

		_this.getPlayOrPauseButton = function () {
			if (_this.props.paused) {
				return React.createElement(
					"button",
					{ type: "button", onClick: _this.play, className: _this.getButtonClasses("play"), title: "Play" },
					React.createElement("i", { className: "fas fa-play" })
				);
			} else {
				return React.createElement(
					"button",
					{ type: "button", onClick: _this.pause, className: _this.getButtonClasses("pause"), title: "Pause" },
					React.createElement("i", { className: "fas fa-pause" })
				);
			}
		};

		_this.inputChanged = function (attr) {
			return function (ev) {
				_this.props.onInputChanged(attr, ev.target.value);
			};
		};

		_this.checkboxChanged = function (attr) {
			return function (ev) {
				_this.props.onCheckboxChanged(attr, ev.target.checked);
			};
		};

		_this.getButtonClasses = function (button) {
			var classes = "btn btn-default btn-info";
			if (button == "back") {
				classes += " mr-2";
			} else if (button == "repeat") {
				classes += " ml-2";
				if (_this.props.repeat) {
					classes += " active";
				}
			}
			return classes;
		};

		_this.state = {};
		return _this;
	}

	_createClass(PlayBar, [{
		key: "render",
		value: function render() {
			return React.createElement(
				"div",
				{ id: "play-bar", className: "container mt-2" },
				React.createElement(
					"div",
					{ className: "row" },
					React.createElement(
						"div",
						{ className: "input-group col-md-3" },
						React.createElement(
							"div",
							{ className: "input-group-prepend" },
							React.createElement(
								"span",
								{ className: "input-group-text" },
								"Time Step"
							)
						),
						React.createElement("input", { type: "text", className: "form-control", defaultValue: this.props.env.timeStep, onChange: this.inputChanged("timeStep") })
					),
					React.createElement("div", { className: "col-md-2" }),
					React.createElement(
						"div",
						{ className: "col-md-2" },
						React.createElement(
							"button",
							{ type: "button", onClick: this.reset, className: this.getButtonClasses("back"), title: "Back" },
							React.createElement("i", { className: "fas fa-backward" })
						),
						this.getPlayOrPauseButton(),
						React.createElement(
							"button",
							{ type: "button", onClick: this.repeat, className: this.getButtonClasses("repeat"), title: "Repeat" },
							React.createElement("i", { className: "fas fa-redo-alt" })
						)
					),
					React.createElement(
						"div",
						{ className: "col-md-3" },
						"Show Path: ",
						React.createElement("input", { type: "checkbox", id: "show-path", name: "Show Path", onChange: this.checkboxChanged("showPath") })
					),
					React.createElement(
						"div",
						{ className: "col-md-2" },
						"time: ",
						this.props.env.time.toFixed(2)
					)
				)
			);
		}
	}]);

	return PlayBar;
}(React.Component);