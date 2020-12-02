'use strict'

class Display extends React.Component {
	constructor(props) {
		super(props);
		this.state = {};
	}

	render() {
		 return (
			<svg id="display" width="1080" height="600" style={{border: '3px solid #000000'}}>
				<circle cx="50" cy="50" r="40" stroke="green" strokeWidth="4" fill="yellow" />
			</svg>
		 );
	}

}
