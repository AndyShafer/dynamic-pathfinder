'use strict';

var _createClass = function () { function defineProperties(target, props) { for (var i = 0; i < props.length; i++) { var descriptor = props[i]; descriptor.enumerable = descriptor.enumerable || false; descriptor.configurable = true; if ("value" in descriptor) descriptor.writable = true; Object.defineProperty(target, descriptor.key, descriptor); } } return function (Constructor, protoProps, staticProps) { if (protoProps) defineProperties(Constructor.prototype, protoProps); if (staticProps) defineProperties(Constructor, staticProps); return Constructor; }; }();

function _classCallCheck(instance, Constructor) { if (!(instance instanceof Constructor)) { throw new TypeError("Cannot call a class as a function"); } }

function _possibleConstructorReturn(self, call) { if (!self) { throw new ReferenceError("this hasn't been initialised - super() hasn't been called"); } return call && (typeof call === "object" || typeof call === "function") ? call : self; }

function _inherits(subClass, superClass) { if (typeof superClass !== "function" && superClass !== null) { throw new TypeError("Super expression must either be null or a function, not " + typeof superClass); } subClass.prototype = Object.create(superClass && superClass.prototype, { constructor: { value: subClass, enumerable: false, writable: true, configurable: true } }); if (superClass) Object.setPrototypeOf ? Object.setPrototypeOf(subClass, superClass) : subClass.__proto__ = superClass; }

var ControlBar = function (_React$Component) {
	_inherits(ControlBar, _React$Component);

	function ControlBar(props) {
		_classCallCheck(this, ControlBar);

		var _this = _possibleConstructorReturn(this, (ControlBar.__proto__ || Object.getPrototypeOf(ControlBar)).call(this, props));

		_this.editClicked = function () {
			_this.props.setMode("edit");
		};

		_this.wallClicked = function () {
			_this.props.setMode("draw-wall");
		};

		_this.panClicked = function () {
			_this.props.setMode("pan");
		};

		_this.inputChanged = function (attr) {
			return function (ev) {
				_this.props.onInputChanged(attr, ev.target.value);
			};
		};

		_this.renderInput = function (field, value) {
			if (_this.props.dragging) {
				return React.createElement("input", { type: "text", className: "form-control", value: value, onChange: _this.inputChanged(field) });
			}
			return React.createElement("input", { type: "text", className: "form-control", defaultValue: value, onChange: _this.inputChanged(field) });
		};

		_this.makeAttributeInputs = function () {
			return Object.entries(_this.props.selectedAttributes).map(function (attr) {
				return React.createElement(
					"div",
					{ key: attr[0], className: "input-group col-md-2" },
					React.createElement(
						"div",
						{ className: "input-group-prepend" },
						React.createElement(
							"span",
							{ className: "input-group-text" },
							attr[0]
						)
					),
					_this.renderInput(attr[0], attr[1])
				);
			});
		};

		_this.getButtonClasses = function (mode) {
			var classes = "btn btn-default btn-secondary";
			if (mode == "draw-wall" || mode == "pan") {
				classes += " ml-2";
			}
			if (mode == _this.props.mode) {
				classes += " active";
			}
			return classes;
		};

		_this.state = {};
		return _this;
	}

	_createClass(ControlBar, [{
		key: "render",
		value: function render() {
			return React.createElement(
				"div",
				{ id: "control-bar", className: "container mb-2 mt-2" },
				React.createElement(
					"div",
					{ className: "row" },
					React.createElement(
						"div",
						{ className: "col-md-2" },
						React.createElement(
							"button",
							{ type: "button", onClick: this.editClicked, className: this.getButtonClasses("edit"), title: "Edit" },
							React.createElement("i", { className: "fas fa-edit" })
						),
						React.createElement(
							"button",
							{ type: "button", onClick: this.wallClicked, className: this.getButtonClasses("draw-wall"), title: "Draw Wall" },
							React.createElement("i", { className: "fas fa-pencil-alt" })
						),
						React.createElement(
							"button",
							{ type: "button", onClick: this.panClicked, className: this.getButtonClasses("pan"), title: "Pan" },
							React.createElement("i", { className: "fas fa-hand-paper" })
						)
					),
					React.createElement(
						"div",
						{ className: "input-group col-md-2" },
						React.createElement(
							"div",
							{ className: "input-group-prepend" },
							React.createElement(
								"span",
								{ className: "input-group-text" },
								"speed"
							)
						),
						React.createElement("input", { type: "text", className: "form-control", defaultValue: this.props.env.speed, onChange: this.inputChanged("speed") })
					),
					this.makeAttributeInputs()
				)
			);
		}
	}]);

	return ControlBar;
}(React.Component);