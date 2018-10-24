var express = require('express');
var router = express.Router();
var fs = require('fs');

/* GET home, index page. */
/*
router.get('/', function(req, res, next) {	
  res.render('index', { title: 'Express' });
});

module.exports = router;
*/


// html 위치로 변경해주기 
router.get('/', function(req, res, next) {	
  fs.readFile('index.html', function(error, data) {
		if(error) {
			console.log(error);
		} else {
			res.writeHead(200);
			res.end(data);
		}
	});
});

module.exports = router;
