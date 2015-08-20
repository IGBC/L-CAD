
#list of natively supported gate types
gateTypes = {'gateAND':  {'label': 'AND' , 'maxinputs': -1, 'function': lambda inputs: reduce(lambda x, y: x and y, inputs),},
			 'gateOR':   {'label': 'OR'  , 'maxinputs': -1, 'function': lambda inputs: reduce(lambda x, y: x or y,  inputs),},
			 'gateNOT':  {'label': 'NOT' , 'maxinputs': 1,  'function': lambda inputs: not inputs,},

			 'gateNAND': {'label': 'NAND', 'maxinputs': -1, 'function': lambda inputs: not reduce(lambda x, y: x and y, inputs),},
			 'gateNOR':  {'label': 'NOR' , 'maxinputs': -1, 'function': lambda inputs: not reduce(lambda x, y: x or y,  inputs),},

			 'gateXOR':  {'label': 'XOR' , 'maxinputs': 2,  'function': lambda inputs: reduce(lambda x, y: (x or y) and (not x and y), inputs),},
			 'gateXNOR': {'label': 'XNOR', 'maxinputs': 2,  'function': lambda inputs: not reduce(lambda x, y: (x or y) and (not x and y), inputs),},
}

class LogicGate:
	def __init__(self, Type):
		self._type = Type #type of logic gate
		self._state = False #output state of the gate
		self._updated = False #updated this "tick"
		self._inputs = [] #gates this gate accepts input from
		#self.outputs = [] #gates this gate outputs to

	def update(self):
		if not updated:
			self._state=self._type['function']()

	#adders and removerers (they're sorta like setters and getters, just not)
	def addInput(self, gate):
		if (len(_inputs) < self.type['maxinputs']) or (self.type['maxinputs'] < 0):
			self._inputs.add(gate)
		else:
			pass #TODO: some error raising?

	def remInput(self, gate):
		self._inputs.remove(gate)

	#Actual setters and getters
	def getState(self):
		return self._state

	def getType(self):
		return self._typedef