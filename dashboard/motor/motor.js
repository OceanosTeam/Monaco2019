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
