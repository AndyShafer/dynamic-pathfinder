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

	makeAttributeInputs = () => {
		return Object.entries(this.props.selectedAttributes).map(attr => { return (
			<div className="input-group col-md-2">
				<div className="input-group-prepend">
    					<span className="input-group-text">{attr[0]}</span>
  				</div>
				<input type="text" className="form-control" value={attr[1]} />
			</div>
		); });
	}

	render() {
		return (
			<div id="control-bar" className="container mb-2 ">
				<div className="row">
					<div className="col-md-2">
						<button type="button" onClick={this.moveClicked} className="btn btn-default btn-primary">M</button>
						<button type="button" onClick={this.selectClicked} className="btn btn-default btn-primary">S</button>
						<button type="button" onClick={this.wallClicked} className="btn btn-default btn-primary">W</button>
						<button type="button" onClick={this.panClicked} className="btn btn-default btn-primary">P</button>
					</div>
					<div className="input-group col-md-2">
						<div className="input-group-prepend">
    							<span className="input-group-text">speed</span>
  						</div>
						<input type="text" className="form-control" value="25" />
					</div>
					{ this.makeAttributeInputs() }
				</div>
			</div>
		);
	}
}
