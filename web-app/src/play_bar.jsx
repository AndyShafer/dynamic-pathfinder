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

	getPlayOrPauseButton = () => {
		if(this.props.paused) {
			return <button type="button" onClick={this.play} className="btn btn-default btn-primary">Play</button>
		} else {
			return <button type="button" onClick={this.pause} className="btn btn-default btn-primary">Pause</button>
		}
	}

	render() {
		 return (
			<div id="play-bar" style={{border: '3px solid #000000'}}>
				<button type="button" className="btn btn-default btn-primary">Back</button>
			 	{ this.getPlayOrPauseButton() }
				<button type="button" className="btn btn-default btn-primary">Replay</button>
			</div>
		 );
	}
}
