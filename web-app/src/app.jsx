'use strict';


const e = React.createElement;

class App extends React.Component {
	constructor(props) {
		super(props);
		this.state = {};
	}

	render() {
		return (
			<div>
				<ControlBar />
				<Display />
				<PlayBar />
			</div>
		);
	}
}


const domContainer = document.querySelector('#app_container');
ReactDOM.render(React.createElement(App), domContainer);
