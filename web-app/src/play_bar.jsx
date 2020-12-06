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

	repeat = () => {
		this.props.onRepeatClicked();
	}

	getPlayOrPauseButton = () => {
		if(this.props.paused) {
			return <button type="button" onClick={this.play} className={ this.getButtonClasses("play") } title="Play"><i className="fas fa-play"></i></button>
		} else {
			return <button type="button" onClick={this.pause} className={ this.getButtonClasses("pause") } title="Pause"><i className="fas fa-pause"></i></button>
		}
	}

	inputChanged = attr => {
		return (ev) => { this.props.onInputChanged(attr, ev.target.value); };
	}

	checkboxChanged = attr => {
		return (ev) => { this.props.onCheckboxChanged(attr, ev.target.checked); };
	}

	getButtonClasses = (button) => {
		var classes = "btn btn-default btn-info";
		if(button == "back") {
			classes += " mr-2";
		} else if(button == "repeat") {
			classes += " ml-2";
			if(this.props.repeat) {
				classes += " active";
			}
		}
		return classes;
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
			 		<div className="col-md-2"></div>
			 		<div className="col-md-2">
						<button type="button" onClick={this.reset} className={ this.getButtonClasses("back") } title="Back"><i className="fas fa-backward"></i></button>
				 		{ this.getPlayOrPauseButton() }
						<button type="button" onClick={this.repeat} className={ this.getButtonClasses("repeat") } title="Repeat"><i className="fas fa-redo-alt"></i></button>
			 		</div>
			 		<div className="col-md-3">Show Path: <input type="checkbox" id="show-path" name="Show Path" onChange={ this.checkboxChanged("showPath") }></input></div>
			 		<div className="col-md-2">time: {this.props.env.time.toFixed(2)}</div>
			 	</div>
			</div>
		 );
	}
}
