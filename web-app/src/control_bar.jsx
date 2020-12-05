'use strict'

class ControlBar extends React.Component {
	constructor(props) {
		super(props);
		this.state = {};
	}

	editClicked = () => {
		this.props.setMode("edit");
	}

	wallClicked = () => {
		this.props.setMode("draw-wall");
	}

	panClicked = () => {
		this.props.setMode("pan");
	}

	inputChanged = attr => {
		return (ev) => { this.props.onInputChanged(attr, ev.target.value); };
	}

	makeAttributeInputs = () => {
		return Object.entries(this.props.selectedAttributes).map(attr => { return (
			<div key={attr[0]} className="input-group col-md-2">
				<div className="input-group-prepend">
    					<span className="input-group-text">{attr[0]}</span>
  				</div>
				<input type="text" className="form-control" value={attr[1]} onChange={ this.inputChanged(attr[0]) }/>
			</div>
		); });
	}

	render() {
		return (
			<div id="control-bar" className="container mb-2 mt-2">
				<div className="row">
					<div className="col-md-2">
						<button type="button" onClick={this.editClicked} className="btn btn-default btn-primary">E</button>
						<button type="button" onClick={this.wallClicked} className="btn btn-default btn-primary">W</button>
						<button type="button" onClick={this.panClicked} className="btn btn-default btn-primary">P</button>
					</div>
					<div className="input-group col-md-2">
						<div className="input-group-prepend">
    							<span className="input-group-text">speed</span>
  						</div>
						<input type="text" className="form-control" value={this.props.env.speed} onChange={ this.inputChanged("speed") } />
					</div>
					{ this.makeAttributeInputs() }
				</div>
			</div>
		);
	}
}
