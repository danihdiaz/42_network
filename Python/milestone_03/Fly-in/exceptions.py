class ParseError(Exception):
    def __init__(self, line_nb: int, message: str):
        self.line_nb = line_nb
        self.message = message
        super().__init__(f"Error in line {line_nb}: {message}")