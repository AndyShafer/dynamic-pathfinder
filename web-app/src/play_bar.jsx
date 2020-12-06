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
			return <button type="button" onClick={this.play} className="btn btn-default btn-primary" title="Play"><i className="fas fa-play"></i></button>
		} else {
			return <button type="button" onClick={this.pause} className="btn btn-default btn-primary" title="Pause"><i className="fas fa-pause"></i></button>
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
						<button type="button" onClick={this.reset} className="btn btn-default btn-primary mr-2" title="Back"><i className="fas fa-backward"></i></button>
				 		{ this.getPlayOrPauseButton() }
						<button type="button" className="btn btn-default btn-primary ml-2" title="Repeat"><i className="fas fa-redo-alt"></i></button>
			 		</div>
			 	</div>
			</div>
		 );
	}
}
