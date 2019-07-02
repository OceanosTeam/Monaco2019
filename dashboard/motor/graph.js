var presets = window.chartColors;
var utils = Samples.utils;
var inputs = {
	min: 0,
	max: 100,
	count: 0,
	decimals: 2,
	continuity: 1
};

new Chart('chart-false', {
	type: line,
	data: [{
		labels: 'Temperature2',
		datasets: [{
			backgroundColor: utils.transparentize(preset.red),
			borderColor: presets.red,
			data: [1,2,3,4,5],
			label: 'Temperature',
			fill: boundary
		}]
	},
	options: Chart.helpers.merge(options, {
		title: {
			text: 'WHAT IS THIS",
			display: true
		}
	})
});
	 
		 
