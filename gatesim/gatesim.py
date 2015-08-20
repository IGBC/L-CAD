#imports
import sys, time
import gate_logic

from PyQt4 import QtGui, QtCore, uic

class GSMainWindow(QtGui.QMainWindow):
    def __init__(self, parent=None):
        #super constructor
        QtGui.QWidget.__init__(self, parent)

        #load and compile ui from file
        self.ui = uic.loadUi('ui/gatesim.ui', self)
        
        #bind ui to functions
        #self.bind_ui()

        self.show()

#this seems to be the python entry point
if __name__ == '__main__':
    app = QtGui.QApplication(sys.argv)
    gatesim = GSMainWindow()
    gatesim.show()
    sys.exit(app.exec_()) 