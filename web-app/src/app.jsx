'use strict';


const e = React.createElement;

class App extends React.Component {
	constructor(props) {
		super(props);
		this.state = {};
	}

	render() {
		return (
			<React.Fragment>
				<div className="row"><div className="col"><ControlBar /></div></div>
				<div className="row"><div className="col"><Display /></div></div>
				<div className="row"><div className="col"><PlayBar /></div></div>
			</React.Fragment>
		);
	}
}

function draw() {
	var canvas = document.getElementById("display");
	var ctx = canvas.getContext("2d")
	ctx.fillStyle = "#FF0000";
	ctx.fillRect(0, 0, 150, 75);
}

const domContainer = document.querySelector('#app_container');
ReactDOM.render(React.createElement(App), domContainer);
draw();
