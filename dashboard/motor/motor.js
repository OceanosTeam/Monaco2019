/*
    Copyright (C) 2018  Técnico Solar Boat

    This program is free software: you can redistribute 
    it and/or modify it under the terms of the GNU General Public License 
    as published by the Free Software Foundation, either version 3 of the 
    License, or (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.

    You can contact Técnico Solar Boat by email at: tecnico.solarboat@gmail.com
    or via our facebook page at https://fb.com/tecnico.solarboat 
*/
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
var presets = window.chartColors;
var speed_gauge;
speed_gauge = new JustGage({
    id: "speed_gauge1",
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
    max: 2000,
    gaugeWidthScale: 0.3,
    counter: true,
    hideInnerShadow: true,
});

var Motor;
setInterval(function() {
    $.ajax({
        type: "GET",
        url: "motor.php",
        dataType: "JSON",
        fail: function(e){
            console.log("FAILED");
        },
        success: function(response) {
            Motor = response;
            speed_gauge.refresh(Motor.RPM);
        }
    });
}, 1000);
