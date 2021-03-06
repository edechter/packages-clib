/*
** Copyright 1998 - 1999 Double Precision, Inc.
** See COPYING for distribution information.
*/

/*
** $Id$
*/
#include	"rfc822.h"
#include	<stdlib.h>

static void cntlen(char c, void *p)
{
	if (c != '\n')
		++ *(size_t *)p;
}

static void saveaddr(char c, void *p)
{
	if (c != '\n')
	{
	char **cp=(char **)p;

		*(*cp)++=c;
	}
}

char *rfc822_getaddr(const struct rfc822a *rfc, int n)
{
size_t	addrbuflen=0;
char	*addrbuf, *ptr;

	rfc822_praddr(rfc, n, &cntlen, &addrbuflen);
	if (!(addrbuf=malloc(addrbuflen+1)))
		return (0);

	ptr=addrbuf;
	rfc822_praddr(rfc, n, &saveaddr, &ptr);
	addrbuf[addrbuflen]=0;
	return (addrbuf);
}

char *rfc822_getname(const struct rfc822a *rfc, int n)
{
char	*p, *q;
size_t	addrbuflen=0;
char	*addrbuf, *ptr;

	rfc822_prname(rfc, n, &cntlen, &addrbuflen);
	if (!(addrbuf=malloc(addrbuflen+1)))
		return (0);

	ptr=addrbuf;
	rfc822_prname(rfc, n, &saveaddr, &ptr);
	addrbuf[addrbuflen]=0;

	/* Get rid of surrounding quotes */

	for (p=q=addrbuf; *p; p++)
		if (*p != '"')	*q++=*p;
	*q=0;
	return (addrbuf);
}

char *rfc822_getname_orlist(const struct rfc822a *rfc, int n)
{
char	*p, *q;
size_t	addrbuflen=0;
char	*addrbuf, *ptr;

	rfc822_prname_orlist(rfc, n, &cntlen, &addrbuflen);
	if (!(addrbuf=malloc(addrbuflen+1)))
		return (0);

	ptr=addrbuf;
	rfc822_prname_orlist(rfc, n, &saveaddr, &ptr);
	addrbuf[addrbuflen]=0;

	/* Get rid of surrounding quotes */

	for (p=q=addrbuf; *p; p++)
		if (*p != '"')	*q++=*p;
	*q=0;
	return (addrbuf);
}

char *rfc822_gettok(const struct rfc822token *t)
{
size_t	addrbuflen=0;
char	*addrbuf, *ptr;

	rfc822tok_print(t, &cntlen, &addrbuflen);

	if (!(addrbuf=malloc(addrbuflen+1)))
		return (0);

	ptr=addrbuf;
	rfc822tok_print(t, &saveaddr, &ptr);
	addrbuf[addrbuflen]=0;
	return (addrbuf);
}
