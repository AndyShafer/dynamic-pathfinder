'use strict'

class Display extends React.Component {
	constructor(props) {
		super(props);
		this.state = {};
	}

	render() {
		 return <canvas id="myCanvas" width="1200" height="700" style={{border: '3px solid #000000'}}></canvas>;
	}
}
