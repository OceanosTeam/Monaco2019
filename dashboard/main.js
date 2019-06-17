window.chartColors = {
    red: 'rgb(255, 50, 32)',
    orange: 'rgb(255, 159, 64)',
    yellow: 'rgb(255, 205, 86)',
    green: 'rgb(75, 192, 92)',
    blue: 'rgb(54, 162, 235)',
    purple: 'rgb(153, 102, 255)',
    grey: 'rgb(201, 203, 207)',
    black: 'rgb(0,0,0)',
    white:'rgb(255,255,255)'
};

function rgbToHex(rgb_color) {
    var res = rgb_color.split("rgb(")[1].split(")")[0].split(",");
    [r,g,b] = [parseInt(res[0]),parseInt(res[1]),parseInt(res[2])];
    return "#" + ((1 << 24) + (r << 16) + (g << 8) + b).toString(16).slice(1);
}
$(document).ready(function(){
    var presets = window.chartColors;
    var speed_gauge;
    speed_gauge = new JustGage({
        id: "speed_gauge",
        title: "Ship Speed",
        label: "KN",
        titleFontColor: presets.black,
        valueFontColor : presets.black,
        gaugeColor : presets.white,
        labelFontColor : presets.black,
        levelColors: [
            rgbToHex(presets.green),
            rgbToHex(presets.yellow),
            rgbToHex(presets.orange),
            rgbToHex(presets.red)
        ],  
        titleMinFontSize: 20,
        decimals: true,
        pointer: true,
        value: 0,
        min: 0,
        max: 10,
        gaugeWidthScale: 0.3,
        counter: true,
        hideInnerShadow: true,
    });
    var engine_gauge;
    engine_gauge= new JustGage({
        id: "engine_gauge",
        title: "Engine RPM",
        label: "RPM",
        titleFontColor: presets.black,
        valueFontColor : presets.black,
        gaugeColor : presets.white,
        labelFontColor : presets.black,
        levelColors: [
            rgbToHex(presets.green),
            rgbToHex(presets.yellow),
            rgbToHex(presets.orange),
            rgbToHex(presets.red)
        ],  
        titleMinFontSize: 20,
        pointer: true,
        value: 0,
        min: 0,
        max: 2200,
        gaugeWidthScale: 0.63,
        counter: true,
        hideInnerShadow: true,
    });

    var g3;
    g3 = new JustGage({
        id: "g3",
        title: "Engine Temp",
        label: "K",
        titleFontColor: "white",
        titleMinFontSize: 20,
        pointer: true,
        value: 0,
        min: 0,
        max: 2200,
        gaugeWidthScale: 0.3,
        counter: true,
        hideInnerShadow: true,
    });

    var g4;
    g4 = new JustGage({
        id: "g4",
        title: "Battery Temp",
        label: "K",
        titleFontColor: "white",
        titleMinFontSize: 20,
        pointer: true,
        value: 0,
        min: 0,
        max: 2200,
        gaugeWidthScale: 0.3,
        counter: true,
        hideInnerShadow: true,
    });
    
    setInterval(function() {
        speed_gauge.refresh((Math.random() * (8.8 - 7.8) + 7.8).toFixed(1));
        engine_gauge.refresh(getRandomInt(1700, 1800));

        //g3.refresh(getRandomInt(1700, 1800));
        //g4.refresh(getRandomInt(1700, 1800));
        
      }, 1000);
});
