from django.conf.urls.defaults import *

# Uncomment the next two lines to enable the admin:
from django.contrib import admin
admin.autodiscover()

urlpatterns = patterns('',
    # Example:
    # (r'^inventory/', include('inventory.viewer.urls'))
    (r'^polls/', include('inventory.polls.urls')),
    # Uncomment the next line to enable the admin:
    (r'^admin/', include(admin.site.urls))
)

# Uncomment the admin/doc line below to enable admin documentation:
urlpatterns += patterns('django.contrib.admindocs', (r'^admin/doc/', include('urls')))

