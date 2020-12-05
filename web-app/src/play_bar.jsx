'use strict'

class PlayBar extends React.Component {
	constructor(props) {
		super(props);
		this.state = {};
	}

	play = () => {
		this.props.onPlayClicked();
	}

	pause = () => {
		this.props.onPauseClicked();
	}

	reset = () => {
		this.props.onResetClicked();
	}

	getPlayOrPauseButton = () => {
		if(this.props.paused) {
			return <button type="button" onClick={this.play} className="btn btn-default btn-primary">Play</button>
		} else {
			return <button type="button" onClick={this.pause} className="btn btn-default btn-primary">Pause</button>
		}
	}

	inputChanged = attr => {
		return (ev) => { this.props.onInputChanged(attr, ev.target.value); };
	}

	render() {
		 return (
			<div id="play-bar" className="container mt-2">
			 	<div className="row">
					<div className="input-group col-md-3">
						<div className="input-group-prepend">
    							<span className="input-group-text">Time Step</span>
  						</div>
						<input type="text" className="form-control" defaultValue={this.props.env.timeStep} onChange={ this.inputChanged("timeStep") } />
					</div>
			 		<div className="col-md-6">
						<button type="button" onClick={this.reset} className="btn btn-default btn-primary">Back</button>
				 		{ this.getPlayOrPauseButton() }
						<button type="button" className="btn btn-default btn-primary">Replay</button>
			 		</div>
			 	</div>
			</div>
		 );
	}
}
