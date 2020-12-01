'use strict'

class PlayBar extends React.Component {
	constructor(props) {
		super(props);
		this.state = {};
	}

	render() {
		 return (
			<div id="play-bar" style={{border: '3px solid #000000'}}>
				<button type="button" className="btn btn-default btn-primary">Back</button>
				<button type="button" className="btn btn-default btn-primary">Play</button>
				<button type="button" className="btn btn-default btn-primary">Replay</button>
			</div>
		 );
	}
}
