const cellSize = 36;

const MaxSquareViz = ({ matrix, square, candidate }) => {
  const rows = matrix.length;
  const cols = matrix[0].length;
  const w = cols * cellSize;
  const h = rows * cellSize;

  return (
    <svg viewBox={`0 0 ${w} ${h}`} width={w} height={h} role="img">
      {matrix.map((row, r) =>
        row.map((val, c) => (
          <g key={`${r}-${c}`}>
            <rect
              x={c * cellSize}
              y={r * cellSize}
              width={cellSize}
              height={cellSize}
              fill="white"
              stroke="#555"
              strokeWidth="2"
            />
            <text
              x={c * cellSize + cellSize / 2}
              y={r * cellSize + cellSize / 2 + 5}
              textAnchor="middle"
              fontSize="16"
              fill="#111"
            >
              {val}
            </text>
          </g>
        ))
      )}

      {candidate && (
        <rect
          x={candidate.col * cellSize}
          y={candidate.row * cellSize}
          width={candidate.size * cellSize}
          height={candidate.size * cellSize}
          fill="none"
          stroke="#e53935"
          strokeWidth="4"
        />
      )}

      <rect
        x={square.col * cellSize}
        y={square.row * cellSize}
        width={square.size * cellSize}
        height={square.size * cellSize}
        fill="none"
        stroke="#3cb043"
        strokeWidth="4"
      />
    </svg>
  );
};

export default MaxSquareViz;
