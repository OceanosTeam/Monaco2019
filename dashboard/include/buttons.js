var redIcon = L.icon({
    iconUrl: '../include/assets/start.png',
    iconSize:     [50, 50], // size of the icon
});
var yellowIcon = L.icon({
    iconUrl: '../include/assets/buoy.png',
    iconSize:     [25, 25], // size of the icon
});
var mymap;
$("#nav-btn a").click(function(){
    $("#overlay-nav").fadeToggle(200);
    $(this).toggleClass('btn-open-nav').toggleClass('btn-close-nav');
});
$("#map-btn a").click(function(){
    $("#overlay-map").fadeToggle(200);
    $(this).toggleClass('btn-open-map').toggleClass('btn-close-map');
    var center = [43.734344, 7.435083];
    mymap = L.map('mapid',{
        center: center,
        zoom: 16
        /*
        maxBounds: [
            //south west
            [43.734344, 7.435083],
            //north east
            [53.734344, 7.035083]
            ],*/
    })
    L.tileLayer('https://api.tiles.mapbox.com/v4/{id}/{z}/{x}/{y}.png?access_token=pk.eyJ1IjoibWFwYm94IiwiYSI6ImNpejY4NXVycTA2emYycXBndHRqcmZ3N3gifQ.rJcFIG214AriISLbB6B5aw', {
        maxZoom: 18,
        attribution: 'Map data &copy; <a href="https://www.openstreetmap.org/">OpenStreetMap</a> contributors, ' +
            '<a href="https://creativecommons.org/licenses/by-sa/2.0/">CC-BY-SA</a>, ' +
            'Imagery © <a href="https://www.mapbox.com/">Mapbox</a>',
        id: 'mapbox.streets'
    }).addTo(mymap);
    var start = [43.734344, 7.435083];
    var buoys = [[43.72915, 7.435384],[43.737631, 7.453043],[43.73884, 7.441092]];
    L.marker(start, {icon: redIcon}).addTo(mymap).bindPopup("<b>Starting Line</b>");
    for (var key in buoys) {
        L.marker(buoys[key], {icon: yellowIcon}).addTo(mymap).bindPopup("<b>Buoy N"+(parseInt(key)+1).toString()+"</b>");
    };
    L.circle([43.734344, 7.435083], 200, {
        color: 'red',
        fillColor: '#f03',
        fillOpacity: 0.5
    }).addTo(mymap).bindPopup("I am a circle.");
    var latlngs = [
        start,
        buoys[0],
        buoys[1],
        buoys[2],
        start
    ];

    var polyline = L.polyline(latlngs, {color: 'red'}).addTo(mymap);
    //map.fitBounds(polyline.getBounds());
    var popup = L.popup();
    function onMapClick(e) {
        popup
            .setLatLng(e.latlng)
            .setContent("You clicked the map at " + e.latlng.toString())
            .openOn(mymap);
    }

    mymap.on('click', onMapClick);
});
    /*
$('#overlay-nav').on('click', function(){
    $("#overlay-nav").fadeToggle(200);   
    $(".button a").toggleClass('btn-open').toggleClass('btn-close');
    open = false;
});
$('#overlay-map').on('click', function(){
    $("#overlay-map").fadeToggle(200);   
    $(".button a").toggleClass('btn-open').toggleClass('btn-close');
    open = false;
});*/