import pygal
from pygal.style import Style
import datetime
from datetime import datetime

custom_style = Style(
	background='#262428',
 	plot_background='#262428',
 	foreground='#F2AA4CFF',
 	foreground_strong='#F2AA4CFF',
 	foreground_subtle='#630C0D')

def create_graph_det(fishino_id, position, type, values, labels,time ):
	try:
		time = []
		for i in labels:
			f = i.strftime("%H:%M:%S")
			time.append(f)
		graph = pygal.Line(style=custom_style)
		graph.title = "{} detected by {} at {}:".format(type,fishino_id, position)
		graph.x_labels = time
		graph.add(type, values)
		graph_data = graph.render_data_uri()
		return graph_data
	except Exception as e:
		return(str(e))



def create_graph(fishino_id, position, type, values, labels, time):
	try:
		graph = pygal.Line(style=custom_style)
		graph.title = "{} detected by {} at {} {}".format(type,fishino_id, position, time)
		graph.x_labels = labels
		graph.add(type, values)
		graph_data = graph.render_data_uri()
		return graph_data
	except Exception as e:
		return(str(e))
