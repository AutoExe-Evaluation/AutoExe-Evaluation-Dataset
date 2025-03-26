void
mm_request_send(int sock, enum monitor_reqtype type, struct sshbuf *m)
{
	size_t mlen = sshbuf_len(m);
	u_char buf[5];

	debug3_f("entering, type %d", type);

	if (mlen >= 0xffffffff)
		fatal_f("bad length %zu", mlen);
	POKE_U32(buf, mlen + 1);
	buf[4] = (u_char) type;		/* 1st byte of payload is mesg-type */
	if (atomicio(vwrite, sock, buf, sizeof(buf)) != sizeof(buf) ||
	    atomicio(vwrite, sock, sshbuf_mutable_ptr(m), mlen) != mlen) {
		if (errno == EPIPE) {
			debug3_f("monitor fd closed");
			mm_reap();
			cleanup_exit(255);
		}
		fatal_f("write: %s", strerror(errno));
	}
}

void
mm_request_receive(int sock, struct sshbuf *m)
{
	u_char buf[4], *p = NULL;
	u_int msg_len;
	int oerrno, r;

	debug3_f("entering");

	if (atomicio(read, sock, buf, sizeof(buf)) != sizeof(buf)) {
		if (errno == EPIPE) {
			debug3_f("monitor fd closed");
			mm_reap();
			cleanup_exit(255);
		}
		fatal_f("read: %s", strerror(errno));
	}
	msg_len = PEEK_U32(buf);
	if (msg_len > 256 * 1024)
		fatal_f("read: bad msg_len %d", msg_len);
	sshbuf_reset(m);
	if ((r = sshbuf_reserve(m, msg_len, &p)) != 0)
		fatal_fr(r, "reserve");
	if (atomicio(read, sock, p, msg_len) != msg_len) {
		oerrno = errno;
		error_f("read: %s", strerror(errno));
		if (oerrno == EPIPE)
			mm_reap();
		cleanup_exit(255);
	}
}
