'use strict';

function inputChanged(attr, fun) {
	return function (ev) {
		fun(attr, ev.target.value);
	};
}