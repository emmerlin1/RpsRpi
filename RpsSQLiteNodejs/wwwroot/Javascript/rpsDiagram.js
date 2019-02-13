var ajaxForm = new ajaxProxy("/api/rps")

document.addEventListener("DOMContentLoaded", function(event) {
//    ajaxForm.PopulateTable (jsonToTable, handleError);
    reloadChart();
});      

function handleError (data) {
    $("#ajax-error-box").modal('show');
    $("#ajax-error").text("Errorcode:" + data.status + ", Message:" + data.statusText);  
    console.log(data);                           
}

function pad(num, size) {
    var s = num+"";
    while (s.length < size) s = "0" + s;
    return s;
}

function jsonToTable (data) {

    // Clear table
    $('#employeeTable tr').slice(1).remove();

    //if no tbody just select your table 
    var tbody = $('#employeeTable').children('tbody');                            
    var table = tbody.length ? tbody : $('#employeeTable');

    var tableString = "";
    var rpsString = "";
    var arCount = new Array();
    var arRps = new Array();


    for(var i in data) {
        var rpmentry = data[i];
        rpsString = rpmentry.rpslowerend + "." +  pad(rpmentry.hundredth, 2);

        tableString += "<tr><td>" + rpmentry.count
                    + "</td><td>" + rpsString
                    + "</td></tr>";
        arCount.push(rpmentry.count);
        arRps.push(parseFloat(rpsString));


    }

    table.append(tableString);
    var config2 = {
        type: 'line',
        data: {
            labels:  arCount,
            datasets: [{
                label: 'Rounds per Second',
                fill: false,
                backgroundColor: window.chartColors.blue,
                borderColor: window.chartColors.blue,
                data: arRps,
            }]
        },
        options: {
            responsive: true,
            title: {
                display: true,
                text: 'RPS Line Chart'
            },
            tooltips: {
                mode: 'index',
                intersect: false,
            },
            hover: {
                mode: 'nearest',
                intersect: true
            },
            scales: {
                xAxes: [{
                    display: true,
                    scaleLabel: {
                        display: true,
                        labelString: 'Count RPS'
                    }
                }],
                yAxes: [{
                    display: true,
                    scaleLabel: {
                        display: true,
                        labelString: 'RPS'
                    }
                }]
            }
        }
    };
     $("#canvas2").remove();// remov00ing previous canvas element
    //change the data values or add new values for new graph
    $("#chart_box").after("<canvas id='canvas2'></canvas>");

   var ctx2 = document.getElementById('canvas2').getContext('2d');
//    ctx2.clear();


    window.myLine = new Chart(ctx2, config2);
//    window.myLine.clear();
//    ctx2.update();
}    

function reloadChart () {
     ajaxForm.PopulateTable (jsonToTable, handleError);
     setTimeout(reloadChart, 5000);
}
// Form event handlers
$('#refresh').click(function(){
    $("#ajax-error-box").hide();
    ajaxForm.PopulateTable (jsonToTable, handleError);                          
});
