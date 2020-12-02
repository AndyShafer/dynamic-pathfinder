'use strict';


const e = React.createElement;

class App extends React.Component {
	constructor(props) {
		super(props);
		this.state = {
			env: {
				start: {x: 50, y:50},
				end: {x:350, y:250},
				walls: [
					{
						id: 0,
						point1: {x: 100, y: 50, vx: 0, vy: 10},
						point2: {x: 100, y: 150, vx: 10, vy: 0}
					}
				],
				time: 4
			}
		};
	}

	render() {
		return (
			<React.Fragment>
				<div className="row"><div className="col"><ControlBar /></div></div>
				<div className="row"><div className="col"><Display env={this.state.env}/></div></div>
				<div className="row"><div className="col"><PlayBar /></div></div>
			</React.Fragment>
		);
	}
}

const domContainer = document.querySelector('#app_container');
ReactDOM.render(React.createElement(App), domContainer);
