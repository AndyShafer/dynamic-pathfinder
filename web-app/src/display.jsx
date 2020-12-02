'use strict'

class Display extends React.Component {
	constructor(props) {
		super(props);
		this.state = {};
	}

	render() {
		 return (
			<canvas id="display" width="1080" height="600" style={{border: '3px solid #000000'}}></canvas>
		 );
	}

}
