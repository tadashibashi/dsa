function compareArr<T>(a: ArrayLike<T>, b: ArrayLike<T>) {
	if (a.length !== b.length) return false;
	for (let i = 0; i < a.length; ++i)
		if (a[i] !== b[i])
			return false;
	return true;
}

export default compareArr;
