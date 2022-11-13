static int fill(INPUT *s, size_t need, size_t size, size_t yymaxfill)
{
	size_t nread = 0;
    const size_t free = s->tok - s->buf;

    if (s->eof) {
        return 0;
    }

    if (free < need) {
        return 0;
    }
    memmove(s->buf, s->tok, s->lim - s->tok);
    s->lim -= free;
    s->cur -= free;
    s->mar -= free;
    s->tok -= free;
    nread = fread(s->lim, 1, free, s->file);
    s->lim += nread;
    if (s->lim < s->buf + size) {
        s->eof = 1;
        memset(s->lim, 0, yymaxfill);
        s->lim += yymaxfill;
    }
    return 1;
}

