// To run this install node.js for your OS - https://nodejs.org
// Use the console/terminal to switch to the directory, where the files are stored
// First run the following command:
// 		npm install
// Then run this command:
// 		npm start
// Visit http://localhost:3000 for classic web model
// Visit http://localhost:3000/ajax for async (ajax)

const express = require('express')
const bodyParser = require('body-parser')
const app = express()

const cartEntries = []

app.set('view engine', 'ejs');
app.set('views', __dirname);

app.use(bodyParser.json());
app.use(bodyParser.urlencoded({ extended: true }))

app.listen(3000, () => console.log('Server listening on port 3000!'))


//////////// REST-API ////////////////

app.get('/ajax', async function (req, res) {
	res.sendFile('cart.html', { root: __dirname })
})

app.get('/cart', function (req, res) {
	res.set('Content-Type', 'application/json')
	res.json(cartEntries)
})

app.post('/cart', function (req, res) {
	const newId = Date.now()
	cartEntries.push({ id: newId, name: req.body.name, amount: req.body.amount || 1 })
	res.set('Content-Type', 'application/json')
	res.redirect(303, '/cart/' + newId)
})

app.delete('/cart/:id', function (req, res) {
	const found = cartEntries.findIndex(e => e.id == req.params.id)
	if (found > -1) cartEntries.splice(found, 1)
	res.json('Deleted Cart Entry with id ' + req.params.id)
})

app.get('/cart/:id', function (req, res) {
	const found = cartEntries.find(e => e.id == req.params.id)
	res.set('Content-Type', 'application/json')
	res.json(found)
})

app.put('/cart/:id', function (req, res) {
	const found = cartEntries.find(e => e.id == req.params.id)
	if (found) {
		found.amount = req.body.amount || 1
		res.set('Content-Type', 'application/json')
		res.json(found)
	} else {
		res.json('Not found')
	}
})

//////////// Image and Sleep ////////////////

app.get('/cart.gif', function(req, res) {
	res.set('Content-Type', 'image/gif')
	res.sendFile('cart.gif', { root: __dirname })
});

function sleep(ms) {
  return new Promise(resolve => setTimeout(resolve, ms));
}