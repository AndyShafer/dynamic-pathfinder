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


const domContainer = document.querySelector('#app_container');
ReactDOM.render(React.createElement(App), domContainer);
