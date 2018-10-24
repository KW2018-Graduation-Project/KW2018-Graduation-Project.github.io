var express = require('express');
var router = express.Router();
var fs = require('fs');

/* GET style page. */
/*
router.get('/', function(req, res, next) {
  res.render('style', { title: 'Style' });
});

module.exports = router;
*/

router.get('/', function(req, res, next) {	
  fs.readFile('style.html', function(error, data) {
		if(error) {
			console.log(error);
		} else {
			res.writeHead(200);
			res.end(data);
		}
	});
});

module.exports = router;