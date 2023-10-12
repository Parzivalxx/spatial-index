import React, { Dispatch, SetStateAction } from 'react';
import * as d3 from 'd3';
import { Point } from '../../../types/Point';
import { handleMouseDown, handleMouseUp, handleMouseClick } from './mouseMovements';

export const createOrPopulateChart = (
  chartRef: React.RefObject<SVGSVGElement>,
  chartInstance: React.MutableRefObject<null | d3.Selection<SVGSVGElement, unknown, null, undefined>>,
  points: Point[],
  width: number,
  height: number,
  queriedPoints: Point[],
  xScale: d3.ScaleLinear<number, number>,
  yScale: d3.ScaleLinear<number, number>,
  setIsSelecting: Dispatch<SetStateAction<boolean>>,
  setSelectionRect: React.Dispatch<
    React.SetStateAction<{ startX: number; startY: number; endX: number; endY: number }>
  >,
  queryType: string,
  setClickedX: Dispatch<SetStateAction<number>>,
  setClickedY: Dispatch<SetStateAction<number>>,
) => {
  if (!(width && height)) {
    return;
  }

  if (!chartInstance.current) {
    const svg = d3.select(chartRef.current).append('svg').attr('width', width).attr('height', height);
    chartInstance.current = svg;
  }

  const svg = chartInstance.current;

  svg.on('mouseenter', () => {
    setIsSelecting(true);
  });

  if (queryType === 'range') {
    svg
      .on('mousedown', (e) => {
        setIsSelecting(true);
        handleMouseDown(e, setSelectionRect, xScale, yScale);
      })
      .on('mouseup', (e) => {
        handleMouseUp(e, setSelectionRect, xScale, yScale);
        setIsSelecting(false);
      });
  } else if (queryType === 'knn') {
    svg.on('mousedown', (e) => {
      handleMouseClick(e, setClickedX, setClickedY, xScale, yScale);
    });
  }

  const pointsGroup = svg.selectAll('circle').data(points);

  pointsGroup
    .enter()
    .append('circle')
    .attr('cx', (d) => xScale(d.x))
    .attr('cy', (d) => yScale(d.y))
    .attr('r', 3)
    .on('mouseover', (event, d) => {
      // Create a tooltip element
      const tooltip = svg
        .append('text')
        .attr('x', xScale(d.x) + 5) // Adjust the position relative to the circle
        .attr('y', yScale(d.y) - 5)
        .attr('class', 'tooltip')
        .style('font-size', '12px')
        .style('fill', 'black');

      // Display the x and y values
      tooltip.text(`X: ${d.x}, Y: ${d.y}`);
    })
    .on('mouseout', () => {
      // Remove the tooltip when the mouse leaves the circle
      svg.select('.tooltip').remove();
    });

  const queriedPointsGroup = svg.selectAll('.queried-point').data(queriedPoints);

  pointsGroup.exit().remove();
  queriedPointsGroup.exit().remove();

  svg.selectAll('circle').style('fill', (d) => {
    const pointD = d as Point;
    return queriedPoints.some((q) => q.x === pointD.x && q.y === pointD.y) ? 'red' : 'blue';
  });

  return () => {
    if (chartInstance.current) {
      chartInstance.current.selectAll('*').remove();
      chartInstance.current = null;
    }
  };
};
