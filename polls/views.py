from django.shortcuts import render_to_response, get_object_or_404
from django.http import HttpResponseRedirect, HttpResponse
from django.core.urlresolvers import reverse
from django.template import RequestContext
from inventory.polls.models import Choice, Poll

def index(request):
  latest_poll_list = Poll.objects.all().order_by('-pub_date')[:5]
  return render_to_response('polls/index.html',
      { 'latest_poll_list': latest_poll_list })

def detail(request, poll_id):
  poll_object = get_object_or_404(Poll, pk=poll_id)
  return render_to_response('polls/detail.html',
      { 'poll': poll_object, 'error_message': "No error." },
      context_instance=RequestContext(request))

def results(request, poll_id):
  poll_object = get_object_or_404(Poll, pk=poll_id)
  return render_to_response('polls/results.html', { 'poll': poll_object })

def vote(request, poll_id):
  poll_object = get_object_or_404(Poll, pk=poll_id)
  try:
    selected_choice = poll_object.choice_set.get(pk=request.POST['choice'])
  except (KeyError, Choice.DoesNotExist):
    return render_to_response('polls/detail.html',
        { 'poll': poll_object, 'error_message': "You didn't select a choice." },
        context_instance=RequestContext(request))
  else:
    selected_choice.votes += 1
    selected_choice.save()
#    return render_to_response('polls/detail.html',
#        { 'poll': poll_object },
#        context_instance=RequestContext(request))
    return HttpResponseRedirect(
        reverse('inventory.polls.views.results', args=(poll_object.id,))
    )

