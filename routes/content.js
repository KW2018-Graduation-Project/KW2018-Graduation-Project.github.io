var express = require('express');
var router = express.Router();
var fs = require('fs');

/* GET content page. */
/*
router.get('/', function(req, res, next) {
  res.render('content', { title: 'content' });
});

module.exports = router;
*/

router.get('/', function(req, res, next) {	
  fs.readFile('content.html', function(error, data) {
		if(error) {
			console.log(error);
		} else {
			res.writeHead(200);
			res.end(data);
		}
	});
});

module.exports = router;