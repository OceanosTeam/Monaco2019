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
    var motor_voltage;
    motor_voltage = new JustGage({
        id: "motor_voltage",
        title: "Motor Voltage",
        label: "V",
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
        max: 60,
        gaugeWidthScale: 0.3,
        counter: true,
        hideInnerShadow: true,
    });
    var motor_speed;
    motor_speed= new JustGage({
        id: "motor_speed",
        title: "Motor RPM",
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
        max: 4000,
        gaugeWidthScale: 0.63,
        counter: true,
        hideInnerShadow: true,
    });

    var motor_temp;
    motor_temp = new JustGage({
        id: "motor_temp",
        title: "Motor Temp",
        label: "C",
        titleFontColor: "white",
        titleMinFontSize: 20,
        pointer: true,
        value: 0,
        min: 0,
        max: 100,
        gaugeWidthScale: 0.3,
        counter: true,
        hideInnerShadow: true,
    });

    var motor_current;
    motor_current = new JustGage({
        id: "motor_current",
        title: "Motor Current",
        label: "A",
        titleFontColor: "white",
        titleMinFontSize: 20,
        pointer: true,
        value: 0,
        min: 0,
        max: 150,
        gaugeWidthScale: 0.3,
        counter: true,
        hideInnerShadow: true,
    });
    
    setInterval(function() {
        motor_speed.refresh((Math.random() * (8.8 - 7.8) + 7.8).toFixed(1));
        motor_voltage.refresh(getRandomInt(10, 15));

        motor_current.refresh(getRandomInt(20, 30));
        motor_temp.refresh(getRandomInt(30, 32));
        
      }, 1000);
});
