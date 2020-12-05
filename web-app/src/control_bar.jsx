'use strict'

class ControlBar extends React.Component {
	constructor(props) {
		super(props);
		this.state = {};
	}

	moveClicked = () => {
		this.props.setMode("move");
	}
	selectClicked = () => {
		this.props.setMode("select");
	}
	wallClicked = () => {
		this.props.setMode("draw-wall");
	}
	panClicked = () => {
		this.props.setMode("pan");
	}

	render() {
		 return (
		 	<div id="control-bar">
				<button type="button" onClick={this.moveClicked} className="btn btn-default btn-primary">Move</button>
				<button type="button" onClick={this.selectClicked} className="btn btn-default btn-primary">Select</button>
				<button type="button" onClick={this.wallClicked} className="btn btn-default btn-primary">Wall</button>
				<button type="button" onClick={this.panClicked} className="btn btn-default btn-primary">Pan</button>
			</div>
		 );
	}
}
