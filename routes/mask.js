var express = require('express');
var router = express.Router();
var fs = require('fs');

/* GET home page. */
/*
router.get('/', function(req, res, next) {
  res.render('mask', { title: 'mask' });
});
*/

router.get('/', function(req, res, next) {	
  fs.readFile('mask.html', function(error, data) {
		if(error) {
			console.log(error);
		} else {
			res.writeHead(200);
			res.end(data);
		}
	});
});


module.exports = router;
